#include "web_proxy.h"

#include "misc/country.h"
#include "web_manager.h"

using namespace Web;

QHash<QLatin1String, bool> Proxy::blacklisted;
QHash<QString, Proxy::ManagerProxyType> Proxy::type_mapping = {
    {LSTR("http"), Proxy::pt_http},
    {LSTR("https"), Proxy::pt_https},
    {LSTR("socks5"), Proxy::pt_socks5},
    {LSTR("socks5s"), Proxy::pt_socks5s}
};



//https://sockslist.net/
//https://proxyhttp.net/

//http://www.proxy-listen.de/Proxy/Proxyliste.html
//http://proxydb.net/
//https://hidemy.name/en/proxy-list/
//http://www.cool-proxy.net/proxies/http_proxy_list
//http://www.gatherproxy.com/proxylistbycountry




//https://gimmeproxy.com/
Proxy * Proxy::findinSource1(const ManagerProxyType & ptype, const QByteArray & country) {
    QUrlQuery query;

    query.addQueryItem(LSTR("get"), LSTR("true"));
    query.addQueryItem(LSTR("post"), LSTR("true"));
    query.addQueryItem(LSTR("cookies"), LSTR("true"));
    query.addQueryItem(LSTR("referer"), LSTR("true"));

    ////        user-agent 	true/false 	user-agent header support 	http://gimmeproxy.com/api/getProxy?user-agent=false
    ////        port 	integer 	Proxy port 	http://gimmeproxy.com/api/getProxy?port=80
    ////        anonymityLevel 	0/1 	Anonymity level, 1 - anonymous, 0 - not anonymous 	http://gimmeproxy.com/api/getProxy?anonymityLevel=1
    ////        notCountry 	string 	Exclude proxies from some country from search 	http://gimmeproxy.com/api/getProxy?notCountry=US

    if (ptype != pt_any) {
        if (ptype & pt_ssl)
            query.addQueryItem(LSTR("supportsHttps"), LSTR("true"));

        if (ptype & pt_http)
            query.addQueryItem(LSTR("protocol"), LSTR("http"));
        else if (ptype == pt_socks5)
            query.addQueryItem(LSTR("protocol"), LSTR("socks5"));
        else return 0;
    }

    if (!country.isEmpty()) {
        CountryCell * cell = Country::obj().find(country);

        if (!cell)
            return 0;

        query.addQueryItem(LSTR("country"), cell -> name2letters);
    }

    QUrl url = QUrl(QLatin1String("http://gimmeproxy.com/api/getProxy"));
    url.setQuery(query);

    Response * resp = Manager::procGet(url);

    Json json = resp -> toJson();

    if (json.hasKey(QLatin1String("ip"))) {
        return new Proxy(
            (ManagerProxyType)(
                strToType(json.string(LSTR("type"))) |
                    (json.boolean(LSTR("supportsHttps")) ? pt_ssl : pt_none)
            ),
            json.string(LSTR("ip")),
            (quint16)json.string(LSTR("port")).toInt(),
            json.string(LSTR("country")).toUtf8()
        );
    }
    else return  0;
}

//http://www.freeproxylists.net/?c=AF&pt=&pr=&a%5B%5D=0&a%5B%5D=1&a%5B%5D=2&u=80&page=2
Proxy * Proxy::findinSource2(const ManagerProxyType & ptype, const QByteArray & country) {
    QUrlQuery query;

    query.addQueryItem(LSTR("a[]"), LSTR("0")); // with none anonimity
    query.addQueryItem(LSTR("a[]"), LSTR("1")); // with anonimity
    query.addQueryItem(LSTR("a[]"), LSTR("2")); // with hihg anonimity

    query.addQueryItem(LSTR("u"), LSTR("80")); // availability more than 80%

    if (ptype == pt_any)
        query.addQueryItem(LSTR("pt"), LSTR(""));
    else if (ptype == pt_http)
        query.addQueryItem(LSTR("pt"), LSTR("HTTP"));
    else if (ptype == pt_https)
        query.addQueryItem(LSTR("pt"), LSTR("HTTPS"));
    else return 0;

    if (!country.isEmpty()) {
        CountryCell * cell = Country::obj().find(country);

        if (!cell)
            return 0;

        query.addQueryItem(LSTR("c"), cell -> name2letters);
    }

    QUrl url = QUrl(QLatin1String("http://www.freeproxylists.net/"));
    url.setQuery(query);

    int page_num = 1;

    while(true) {
        if (page_num > 1) {
            QUrlQuery cquery(query);
            query.addQueryItem(LSTR("page"), QString::number(page_num));
            url.setQuery(cquery);
        }

        Response * resp = Manager::procGet(url);

        Html::Page page = resp -> toHtml();

        Html::Tag * data_table = page.findFirst("table.DataGrid");

        Html::Set trs = data_table -> find("tr");

        if (page_num > 1 && trs.isEmpty())
            break;

        for(Html::Set::Iterator tr = trs.begin(); tr != trs.end(); tr++) {
            Html::Set children = (*tr) -> children();

            QString ip = QLatin1String(children.first() -> text());
            QRegularExpression reg(LSTR("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"));

            qDebug() << children[4] -> text();
            qDebug() << children[4] -> findFirst("img") -> src();

            if (reg.match(ip).hasMatch()) {
                return new Proxy(
                    strToType(children[2] -> text().toLower()),
                    ip,
                    (quint16)children[1] -> text().toInt(),
                    children[4] -> text()
                );
            }
            else qDebug() << "WRONG RES" << ip;
        }

        if (page_num == 1 && !page.findFirst(".page"))
            break;

        page_num++;
    }

    return 0;
}

//https://www.socks-proxy.net/
Proxy * Proxy::findinSource3(const ManagerProxyType & ptype, const QByteArray & country) {
    if (ptype & pt_http)
        return 0;

    CountryCell * ccell = country.isEmpty() ? 0 : Country::obj().find(country);

    if (!country.isEmpty() && !ccell)
        return 0;

    QUrl url = QUrl(QLatin1String("https://www.socks-proxy.net/"));

    Response * resp = Manager::procGet(url);

    Html::Page page = resp -> toHtml();

    Html::Tag * data_table = page.findFirst("table#proxylisttable");

    Html::Set trs = data_table -> find("tbody tr");

    for(Html::Set::Iterator tr = trs.begin(); tr != trs.end(); tr++) {
        Html::Set children = (*tr) -> children();

        QString ip = QLatin1String(children.first() -> text());
        QRegularExpression reg(LSTR("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"));

        if (reg.match(ip).hasMatch()) {
            ManagerProxyType pt = strToType(children[4] -> text().toLower());
            pt = (ManagerProxyType)(pt | (children[6] -> text() == QByteArrayLiteral("Yes") ? pt_ssl : pt_none));
            QByteArray pcountry = children[3] -> text();
            CountryCell * pccell = Country::obj().find(pcountry);

            if (pt != pt_unsupported && (ptype == pt_any || ptype == pt) && (!ccell || (pccell && pccell -> name2letters == ccell -> name2letters))) {
                return new Proxy(
                    pt,
                    ip,
                    (quint16)children[1] -> text().toInt(),
                    pcountry
                );
            } else qDebug() << "UNSUPPORTED PROTOCOL: " << children[4] -> text().toLower();
        }
        else qDebug() << "WRONG RES" << ip;
    }

    return 0;
}

////http://www.socks24.org/
//Proxy * Proxy::findinSource5(const ManagerProxyType & ptype, const QByteArray & country) {

//}

Proxy * Proxy::find(const ManagerProxyType & ptype, const QByteArray & country) {
    Proxy * res = findinSource1(ptype, country);

//    if (!res) {
//        res = findinSource2(ptype, country);

//        if (!res) {
//            res = findinSource3(ptype, country);
//        }
//    }

    return res;
}
