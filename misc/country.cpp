#include "country.h"

Country::Country() {
    init();
}

void Country::init() {
    CountryCell * cell;

    cell = new CountryCell {QByteArrayLiteral("Aruba"), QByteArrayLiteral("Aruba"), QByteArrayLiteral("AW"), QByteArrayLiteral("ABW"), {}};
    list.insert(QByteArrayLiteral("AW"), cell);
    list.insert(QByteArrayLiteral("ABW"), cell);
    list.insert(QByteArrayLiteral("Aruba"), cell);

    cell = new CountryCell {QByteArrayLiteral("Islamic Republic of Afghanistan"), QByteArrayLiteral("Afghanistan"), QByteArrayLiteral("AF"), QByteArrayLiteral("AFG"), {"IRN", "PAK", "TKM", "UZB", "TJK", "CHN"}};
    list.insert(QByteArrayLiteral("AF"), cell);
    list.insert(QByteArrayLiteral("AFG"), cell);
    list.insert(QByteArrayLiteral("Islamic Republic of Afghanistan"), cell);
    list.insert(QByteArrayLiteral("Afghanistan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Angola"), QByteArrayLiteral("Angola"), QByteArrayLiteral("AO"), QByteArrayLiteral("AGO"), {"COG", "COD", "ZMB", "NAM"}};
    list.insert(QByteArrayLiteral("AO"), cell);
    list.insert(QByteArrayLiteral("AGO"), cell);
    list.insert(QByteArrayLiteral("Republic of Angola"), cell);
    list.insert(QByteArrayLiteral("Angola"), cell);

    cell = new CountryCell {QByteArrayLiteral("Anguilla"), QByteArrayLiteral("Anguilla"), QByteArrayLiteral("AI"), QByteArrayLiteral("AIA"), {}};
    list.insert(QByteArrayLiteral("AI"), cell);
    list.insert(QByteArrayLiteral("AIA"), cell);
    list.insert(QByteArrayLiteral("Anguilla"), cell);

    cell = new CountryCell {QByteArrayLiteral("Aland Islands"), QByteArrayLiteral("Aland Islands"), QByteArrayLiteral("AX"), QByteArrayLiteral("ALA"), {}};
    list.insert(QByteArrayLiteral("AX"), cell);
    list.insert(QByteArrayLiteral("ALA"), cell);
    list.insert(QByteArrayLiteral("Aland Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Albania"), QByteArrayLiteral("Albania"), QByteArrayLiteral("AL"), QByteArrayLiteral("ALB"), {"MNE", "GRC", "MKD", "UNK"}};
    list.insert(QByteArrayLiteral("AL"), cell);
    list.insert(QByteArrayLiteral("ALB"), cell);
    list.insert(QByteArrayLiteral("Republic of Albania"), cell);
    list.insert(QByteArrayLiteral("Albania"), cell);

    cell = new CountryCell {QByteArrayLiteral("Principality of Andorra"), QByteArrayLiteral("Andorra"), QByteArrayLiteral("AD"), QByteArrayLiteral("AND"), {"FRA", "ESP"}};
    list.insert(QByteArrayLiteral("AD"), cell);
    list.insert(QByteArrayLiteral("AND"), cell);
    list.insert(QByteArrayLiteral("Principality of Andorra"), cell);
    list.insert(QByteArrayLiteral("Andorra"), cell);

    cell = new CountryCell {QByteArrayLiteral("United Arab Emirates"), QByteArrayLiteral("United Arab Emirates"), QByteArrayLiteral("AE"), QByteArrayLiteral("ARE"), {"OMN", "SAU"}};
    list.insert(QByteArrayLiteral("AE"), cell);
    list.insert(QByteArrayLiteral("ARE"), cell);
    list.insert(QByteArrayLiteral("United Arab Emirates"), cell);

    cell = new CountryCell {QByteArrayLiteral("Argentine Republic"), QByteArrayLiteral("Argentina"), QByteArrayLiteral("AR"), QByteArrayLiteral("ARG"), {"BOL", "BRA", "CHL", "PRY", "URY"}};
    list.insert(QByteArrayLiteral("AR"), cell);
    list.insert(QByteArrayLiteral("ARG"), cell);
    list.insert(QByteArrayLiteral("Argentine Republic"), cell);
    list.insert(QByteArrayLiteral("Argentina"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Armenia"), QByteArrayLiteral("Armenia"), QByteArrayLiteral("AM"), QByteArrayLiteral("ARM"), {"AZE", "GEO", "IRN", "TUR"}};
    list.insert(QByteArrayLiteral("AM"), cell);
    list.insert(QByteArrayLiteral("ARM"), cell);
    list.insert(QByteArrayLiteral("Republic of Armenia"), cell);
    list.insert(QByteArrayLiteral("Armenia"), cell);

    cell = new CountryCell {QByteArrayLiteral("American Samoa"), QByteArrayLiteral("American Samoa"), QByteArrayLiteral("AS"), QByteArrayLiteral("ASM"), {}};
    list.insert(QByteArrayLiteral("AS"), cell);
    list.insert(QByteArrayLiteral("ASM"), cell);
    list.insert(QByteArrayLiteral("American Samoa"), cell);

    cell = new CountryCell {QByteArrayLiteral("Antarctica"), QByteArrayLiteral("Antarctica"), QByteArrayLiteral("AQ"), QByteArrayLiteral("ATA"), {}};
    list.insert(QByteArrayLiteral("AQ"), cell);
    list.insert(QByteArrayLiteral("ATA"), cell);
    list.insert(QByteArrayLiteral("Antarctica"), cell);

    cell = new CountryCell {QByteArrayLiteral("Territory of the French Southern and Antarctic Lands"), QByteArrayLiteral("French Southern and Antarctic Lands"), QByteArrayLiteral("TF"), QByteArrayLiteral("ATF"), {}};
    list.insert(QByteArrayLiteral("TF"), cell);
    list.insert(QByteArrayLiteral("ATF"), cell);
    list.insert(QByteArrayLiteral("Territory of the French Southern and Antarctic Lands"), cell);
    list.insert(QByteArrayLiteral("French Southern and Antarctic Lands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Antigua and Barbuda"), QByteArrayLiteral("Antigua and Barbuda"), QByteArrayLiteral("AG"), QByteArrayLiteral("ATG"), {}};
    list.insert(QByteArrayLiteral("AG"), cell);
    list.insert(QByteArrayLiteral("ATG"), cell);
    list.insert(QByteArrayLiteral("Antigua and Barbuda"), cell);

    cell = new CountryCell {QByteArrayLiteral("Commonwealth of Australia"), QByteArrayLiteral("Australia"), QByteArrayLiteral("AU"), QByteArrayLiteral("AUS"), {}};
    list.insert(QByteArrayLiteral("AU"), cell);
    list.insert(QByteArrayLiteral("AUS"), cell);
    list.insert(QByteArrayLiteral("Commonwealth of Australia"), cell);
    list.insert(QByteArrayLiteral("Australia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Austria"), QByteArrayLiteral("Austria"), QByteArrayLiteral("AT"), QByteArrayLiteral("AUT"), {"CZE", "DEU", "HUN", "ITA", "LIE", "SVK", "SVN", "CHE"}};
    list.insert(QByteArrayLiteral("AT"), cell);
    list.insert(QByteArrayLiteral("AUT"), cell);
    list.insert(QByteArrayLiteral("Republic of Austria"), cell);
    list.insert(QByteArrayLiteral("Austria"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Azerbaijan"), QByteArrayLiteral("Azerbaijan"), QByteArrayLiteral("AZ"), QByteArrayLiteral("AZE"), {"ARM", "GEO", "IRN", "RUS", "TUR"}};
    list.insert(QByteArrayLiteral("AZ"), cell);
    list.insert(QByteArrayLiteral("AZE"), cell);
    list.insert(QByteArrayLiteral("Republic of Azerbaijan"), cell);
    list.insert(QByteArrayLiteral("Azerbaijan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Burundi"), QByteArrayLiteral("Burundi"), QByteArrayLiteral("BI"), QByteArrayLiteral("BDI"), {"COD", "RWA", "TZA"}};
    list.insert(QByteArrayLiteral("BI"), cell);
    list.insert(QByteArrayLiteral("BDI"), cell);
    list.insert(QByteArrayLiteral("Republic of Burundi"), cell);
    list.insert(QByteArrayLiteral("Burundi"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Belgium"), QByteArrayLiteral("Belgium"), QByteArrayLiteral("BE"), QByteArrayLiteral("BEL"), {"FRA", "DEU", "LUX", "NLD"}};
    list.insert(QByteArrayLiteral("BE"), cell);
    list.insert(QByteArrayLiteral("BEL"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Belgium"), cell);
    list.insert(QByteArrayLiteral("Belgium"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Benin"), QByteArrayLiteral("Benin"), QByteArrayLiteral("BJ"), QByteArrayLiteral("BEN"), {"BFA", "NER", "NGA", "TGO"}};
    list.insert(QByteArrayLiteral("BJ"), cell);
    list.insert(QByteArrayLiteral("BEN"), cell);
    list.insert(QByteArrayLiteral("Republic of Benin"), cell);
    list.insert(QByteArrayLiteral("Benin"), cell);

    cell = new CountryCell {QByteArrayLiteral("Burkina Faso"), QByteArrayLiteral("Burkina Faso"), QByteArrayLiteral("BF"), QByteArrayLiteral("BFA"), {"BEN", "CIV", "GHA", "MLI", "NER", "TGO"}};
    list.insert(QByteArrayLiteral("BF"), cell);
    list.insert(QByteArrayLiteral("BFA"), cell);
    list.insert(QByteArrayLiteral("Burkina Faso"), cell);

    cell = new CountryCell {QByteArrayLiteral("People's Republic of Bangladesh"), QByteArrayLiteral("Bangladesh"), QByteArrayLiteral("BD"), QByteArrayLiteral("BGD"), {"MMR", "IND"}};
    list.insert(QByteArrayLiteral("BD"), cell);
    list.insert(QByteArrayLiteral("BGD"), cell);
    list.insert(QByteArrayLiteral("People's Republic of Bangladesh"), cell);
    list.insert(QByteArrayLiteral("Bangladesh"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Bulgaria"), QByteArrayLiteral("Bulgaria"), QByteArrayLiteral("BG"), QByteArrayLiteral("BGR"), {"GRC", "MKD", "ROU", "SRB", "TUR"}};
    list.insert(QByteArrayLiteral("BG"), cell);
    list.insert(QByteArrayLiteral("BGR"), cell);
    list.insert(QByteArrayLiteral("Republic of Bulgaria"), cell);
    list.insert(QByteArrayLiteral("Bulgaria"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Bahrain"), QByteArrayLiteral("Bahrain"), QByteArrayLiteral("BH"), QByteArrayLiteral("BHR"), {}};
    list.insert(QByteArrayLiteral("BH"), cell);
    list.insert(QByteArrayLiteral("BHR"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Bahrain"), cell);
    list.insert(QByteArrayLiteral("Bahrain"), cell);

    cell = new CountryCell {QByteArrayLiteral("Commonwealth of the Bahamas"), QByteArrayLiteral("Bahamas"), QByteArrayLiteral("BS"), QByteArrayLiteral("BHS"), {}};
    list.insert(QByteArrayLiteral("BS"), cell);
    list.insert(QByteArrayLiteral("BHS"), cell);
    list.insert(QByteArrayLiteral("Commonwealth of the Bahamas"), cell);
    list.insert(QByteArrayLiteral("Bahamas"), cell);

    cell = new CountryCell {QByteArrayLiteral("Bosnia and Herzegovina"), QByteArrayLiteral("Bosnia and Herzegovina"), QByteArrayLiteral("BA"), QByteArrayLiteral("BIH"), {"HRV", "MNE", "SRB"}};
    list.insert(QByteArrayLiteral("BA"), cell);
    list.insert(QByteArrayLiteral("BIH"), cell);
    list.insert(QByteArrayLiteral("Bosnia and Herzegovina"), cell);

    cell = new CountryCell {QByteArrayLiteral("Collectivity of Saint Barthelemy"), QByteArrayLiteral("Saint Barthelemy"), QByteArrayLiteral("BL"), QByteArrayLiteral("BLM"), {}};
    list.insert(QByteArrayLiteral("BL"), cell);
    list.insert(QByteArrayLiteral("BLM"), cell);
    list.insert(QByteArrayLiteral("Collectivity of Saint Barthelemy"), cell);
    list.insert(QByteArrayLiteral("Saint Barthelemy"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Belarus"), QByteArrayLiteral("Belarus"), QByteArrayLiteral("BY"), QByteArrayLiteral("BLR"), {"LVA", "LTU", "POL", "RUS", "UKR"}};
    list.insert(QByteArrayLiteral("BY"), cell);
    list.insert(QByteArrayLiteral("BLR"), cell);
    list.insert(QByteArrayLiteral("Republic of Belarus"), cell);
    list.insert(QByteArrayLiteral("Belarus"), cell);

    cell = new CountryCell {QByteArrayLiteral("Belize"), QByteArrayLiteral("Belize"), QByteArrayLiteral("BZ"), QByteArrayLiteral("BLZ"), {"GTM", "MEX"}};
    list.insert(QByteArrayLiteral("BZ"), cell);
    list.insert(QByteArrayLiteral("BLZ"), cell);
    list.insert(QByteArrayLiteral("Belize"), cell);

    cell = new CountryCell {QByteArrayLiteral("Bermuda"), QByteArrayLiteral("Bermuda"), QByteArrayLiteral("BM"), QByteArrayLiteral("BMU"), {}};
    list.insert(QByteArrayLiteral("BM"), cell);
    list.insert(QByteArrayLiteral("BMU"), cell);
    list.insert(QByteArrayLiteral("Bermuda"), cell);

    cell = new CountryCell {QByteArrayLiteral("Plurinational State of Bolivia"), QByteArrayLiteral("Bolivia"), QByteArrayLiteral("BO"), QByteArrayLiteral("BOL"), {"ARG", "BRA", "CHL", "PRY", "PER"}};
    list.insert(QByteArrayLiteral("BO"), cell);
    list.insert(QByteArrayLiteral("BOL"), cell);
    list.insert(QByteArrayLiteral("Plurinational State of Bolivia"), cell);
    list.insert(QByteArrayLiteral("Bolivia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federative Republic of Brazil"), QByteArrayLiteral("Brazil"), QByteArrayLiteral("BR"), QByteArrayLiteral("BRA"), {"ARG", "BOL", "COL", "GUF", "GUY", "PRY", "PER", "SUR", "URY", "VEN"}};
    list.insert(QByteArrayLiteral("BR"), cell);
    list.insert(QByteArrayLiteral("BRA"), cell);
    list.insert(QByteArrayLiteral("Federative Republic of Brazil"), cell);
    list.insert(QByteArrayLiteral("Brazil"), cell);

    cell = new CountryCell {QByteArrayLiteral("Barbados"), QByteArrayLiteral("Barbados"), QByteArrayLiteral("BB"), QByteArrayLiteral("BRB"), {}};
    list.insert(QByteArrayLiteral("BB"), cell);
    list.insert(QByteArrayLiteral("BRB"), cell);
    list.insert(QByteArrayLiteral("Barbados"), cell);

    cell = new CountryCell {QByteArrayLiteral("Nation of Brunei, Abode of Peace"), QByteArrayLiteral("Brunei"), QByteArrayLiteral("BN"), QByteArrayLiteral("BRN"), {"MYS"}};
    list.insert(QByteArrayLiteral("BN"), cell);
    list.insert(QByteArrayLiteral("BRN"), cell);
    list.insert(QByteArrayLiteral("Nation of Brunei, Abode of Peace"), cell);
    list.insert(QByteArrayLiteral("Brunei"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Bhutan"), QByteArrayLiteral("Bhutan"), QByteArrayLiteral("BT"), QByteArrayLiteral("BTN"), {"CHN", "IND"}};
    list.insert(QByteArrayLiteral("BT"), cell);
    list.insert(QByteArrayLiteral("BTN"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Bhutan"), cell);
    list.insert(QByteArrayLiteral("Bhutan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Bouvet Island"), QByteArrayLiteral("Bouvet Island"), QByteArrayLiteral("BV"), QByteArrayLiteral("BVT"), {}};
    list.insert(QByteArrayLiteral("BV"), cell);
    list.insert(QByteArrayLiteral("BVT"), cell);
    list.insert(QByteArrayLiteral("Bouvet Island"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Botswana"), QByteArrayLiteral("Botswana"), QByteArrayLiteral("BW"), QByteArrayLiteral("BWA"), {"NAM", "ZAF", "ZMB", "ZWE"}};
    list.insert(QByteArrayLiteral("BW"), cell);
    list.insert(QByteArrayLiteral("BWA"), cell);
    list.insert(QByteArrayLiteral("Republic of Botswana"), cell);
    list.insert(QByteArrayLiteral("Botswana"), cell);

    cell = new CountryCell {QByteArrayLiteral("Central African Republic"), QByteArrayLiteral("Central African Republic"), QByteArrayLiteral("CF"), QByteArrayLiteral("CAF"), {"CMR", "TCD", "COD", "COG", "SSD", "SDN"}};
    list.insert(QByteArrayLiteral("CF"), cell);
    list.insert(QByteArrayLiteral("CAF"), cell);
    list.insert(QByteArrayLiteral("Central African Republic"), cell);

    cell = new CountryCell {QByteArrayLiteral("Canada"), QByteArrayLiteral("Canada"), QByteArrayLiteral("CA"), QByteArrayLiteral("CAN"), {"USA"}};
    list.insert(QByteArrayLiteral("CA"), cell);
    list.insert(QByteArrayLiteral("CAN"), cell);
    list.insert(QByteArrayLiteral("Canada"), cell);

    cell = new CountryCell {QByteArrayLiteral("Territory of the Cocos (Keeling) Islands"), QByteArrayLiteral("Cocos (Keeling) Islands"), QByteArrayLiteral("CC"), QByteArrayLiteral("CCK"), {}};
    list.insert(QByteArrayLiteral("CC"), cell);
    list.insert(QByteArrayLiteral("CCK"), cell);
    list.insert(QByteArrayLiteral("Territory of the Cocos (Keeling) Islands"), cell);
    list.insert(QByteArrayLiteral("Cocos (Keeling) Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Swiss Confederation"), QByteArrayLiteral("Switzerland"), QByteArrayLiteral("CH"), QByteArrayLiteral("CHE"), {"AUT", "FRA", "ITA", "LIE", "DEU"}};
    list.insert(QByteArrayLiteral("CH"), cell);
    list.insert(QByteArrayLiteral("CHE"), cell);
    list.insert(QByteArrayLiteral("Swiss Confederation"), cell);
    list.insert(QByteArrayLiteral("Switzerland"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Chile"), QByteArrayLiteral("Chile"), QByteArrayLiteral("CL"), QByteArrayLiteral("CHL"), {"ARG", "BOL", "PER"}};
    list.insert(QByteArrayLiteral("CL"), cell);
    list.insert(QByteArrayLiteral("CHL"), cell);
    list.insert(QByteArrayLiteral("Republic of Chile"), cell);
    list.insert(QByteArrayLiteral("Chile"), cell);

    cell = new CountryCell {QByteArrayLiteral("People's Republic of China"), QByteArrayLiteral("China"), QByteArrayLiteral("CN"), QByteArrayLiteral("CHN"), {"AFG", "BTN", "MMR", "HKG", "IND", "KAZ", "PRK", "KGZ", "LAO", "MAC", "MNG", "PAK", "RUS", "TJK", "VNM"}};
    list.insert(QByteArrayLiteral("CN"), cell);
    list.insert(QByteArrayLiteral("CHN"), cell);
    list.insert(QByteArrayLiteral("People's Republic of China"), cell);
    list.insert(QByteArrayLiteral("China"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Cote d'Ivoire"), QByteArrayLiteral("Ivory Coast"), QByteArrayLiteral("CI"), QByteArrayLiteral("CIV"), {"BFA", "GHA", "GIN", "LBR", "MLI"}};
    list.insert(QByteArrayLiteral("CI"), cell);
    list.insert(QByteArrayLiteral("CIV"), cell);
    list.insert(QByteArrayLiteral("Republic of Cote d'Ivoire"), cell);
    list.insert(QByteArrayLiteral("Ivory Coast"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Cameroon"), QByteArrayLiteral("Cameroon"), QByteArrayLiteral("CM"), QByteArrayLiteral("CMR"), {"CAF", "TCD", "COG", "GNQ", "GAB", "NGA"}};
    list.insert(QByteArrayLiteral("CM"), cell);
    list.insert(QByteArrayLiteral("CMR"), cell);
    list.insert(QByteArrayLiteral("Republic of Cameroon"), cell);
    list.insert(QByteArrayLiteral("Cameroon"), cell);

    cell = new CountryCell {QByteArrayLiteral("Democratic Republic of the Congo"), QByteArrayLiteral("DR Congo"), QByteArrayLiteral("CD"), QByteArrayLiteral("COD"), {"AGO", "BDI", "CAF", "COG", "RWA", "SSD", "TZA", "UGA", "ZMB"}};
    list.insert(QByteArrayLiteral("CD"), cell);
    list.insert(QByteArrayLiteral("COD"), cell);
    list.insert(QByteArrayLiteral("Democratic Republic of the Congo"), cell);
    list.insert(QByteArrayLiteral("DR Congo"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of the Congo"), QByteArrayLiteral("Republic of the Congo"), QByteArrayLiteral("CG"), QByteArrayLiteral("COG"), {"AGO", "CMR", "CAF", "COD", "GAB"}};
    list.insert(QByteArrayLiteral("CG"), cell);
    list.insert(QByteArrayLiteral("COG"), cell);
    list.insert(QByteArrayLiteral("Republic of the Congo"), cell);

    cell = new CountryCell {QByteArrayLiteral("Cook Islands"), QByteArrayLiteral("Cook Islands"), QByteArrayLiteral("CK"), QByteArrayLiteral("COK"), {}};
    list.insert(QByteArrayLiteral("CK"), cell);
    list.insert(QByteArrayLiteral("COK"), cell);
    list.insert(QByteArrayLiteral("Cook Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Colombia"), QByteArrayLiteral("Colombia"), QByteArrayLiteral("CO"), QByteArrayLiteral("COL"), {"BRA", "ECU", "PAN", "PER", "VEN"}};
    list.insert(QByteArrayLiteral("CO"), cell);
    list.insert(QByteArrayLiteral("COL"), cell);
    list.insert(QByteArrayLiteral("Republic of Colombia"), cell);
    list.insert(QByteArrayLiteral("Colombia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Union of the Comoros"), QByteArrayLiteral("Comoros"), QByteArrayLiteral("KM"), QByteArrayLiteral("COM"), {}};
    list.insert(QByteArrayLiteral("KM"), cell);
    list.insert(QByteArrayLiteral("COM"), cell);
    list.insert(QByteArrayLiteral("Union of the Comoros"), cell);
    list.insert(QByteArrayLiteral("Comoros"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Cabo Verde"), QByteArrayLiteral("Cape Verde"), QByteArrayLiteral("CV"), QByteArrayLiteral("CPV"), {}};
    list.insert(QByteArrayLiteral("CV"), cell);
    list.insert(QByteArrayLiteral("CPV"), cell);
    list.insert(QByteArrayLiteral("Republic of Cabo Verde"), cell);
    list.insert(QByteArrayLiteral("Cape Verde"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Costa Rica"), QByteArrayLiteral("Costa Rica"), QByteArrayLiteral("CR"), QByteArrayLiteral("CRI"), {"NIC", "PAN"}};
    list.insert(QByteArrayLiteral("CR"), cell);
    list.insert(QByteArrayLiteral("CRI"), cell);
    list.insert(QByteArrayLiteral("Republic of Costa Rica"), cell);
    list.insert(QByteArrayLiteral("Costa Rica"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Cuba"), QByteArrayLiteral("Cuba"), QByteArrayLiteral("CU"), QByteArrayLiteral("CUB"), {}};
    list.insert(QByteArrayLiteral("CU"), cell);
    list.insert(QByteArrayLiteral("CUB"), cell);
    list.insert(QByteArrayLiteral("Republic of Cuba"), cell);
    list.insert(QByteArrayLiteral("Cuba"), cell);

    cell = new CountryCell {QByteArrayLiteral("Country of Curacao"), QByteArrayLiteral("Curacao"), QByteArrayLiteral("CW"), QByteArrayLiteral("CUW"), {}};
    list.insert(QByteArrayLiteral("CW"), cell);
    list.insert(QByteArrayLiteral("CUW"), cell);
    list.insert(QByteArrayLiteral("Country of Curacao"), cell);
    list.insert(QByteArrayLiteral("Curacao"), cell);

    cell = new CountryCell {QByteArrayLiteral("Territory of Christmas Island"), QByteArrayLiteral("Christmas Island"), QByteArrayLiteral("CX"), QByteArrayLiteral("CXR"), {}};
    list.insert(QByteArrayLiteral("CX"), cell);
    list.insert(QByteArrayLiteral("CXR"), cell);
    list.insert(QByteArrayLiteral("Territory of Christmas Island"), cell);
    list.insert(QByteArrayLiteral("Christmas Island"), cell);

    cell = new CountryCell {QByteArrayLiteral("Cayman Islands"), QByteArrayLiteral("Cayman Islands"), QByteArrayLiteral("KY"), QByteArrayLiteral("CYM"), {}};
    list.insert(QByteArrayLiteral("KY"), cell);
    list.insert(QByteArrayLiteral("CYM"), cell);
    list.insert(QByteArrayLiteral("Cayman Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Cyprus"), QByteArrayLiteral("Cyprus"), QByteArrayLiteral("CY"), QByteArrayLiteral("CYP"), {"GBR"}};
    list.insert(QByteArrayLiteral("CY"), cell);
    list.insert(QByteArrayLiteral("CYP"), cell);
    list.insert(QByteArrayLiteral("Republic of Cyprus"), cell);
    list.insert(QByteArrayLiteral("Cyprus"), cell);

    cell = new CountryCell {QByteArrayLiteral("Czech Republic"), QByteArrayLiteral("Czechia"), QByteArrayLiteral("CZ"), QByteArrayLiteral("CZE"), {"AUT", "DEU", "POL", "SVK"}};
    list.insert(QByteArrayLiteral("CZ"), cell);
    list.insert(QByteArrayLiteral("CZE"), cell);
    list.insert(QByteArrayLiteral("Czech Republic"), cell);
    list.insert(QByteArrayLiteral("Czechia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federal Republic of Germany"), QByteArrayLiteral("Germany"), QByteArrayLiteral("DE"), QByteArrayLiteral("DEU"), {"AUT", "BEL", "CZE", "DNK", "FRA", "LUX", "NLD", "POL", "CHE"}};
    list.insert(QByteArrayLiteral("DE"), cell);
    list.insert(QByteArrayLiteral("DEU"), cell);
    list.insert(QByteArrayLiteral("Federal Republic of Germany"), cell);
    list.insert(QByteArrayLiteral("Germany"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Djibouti"), QByteArrayLiteral("Djibouti"), QByteArrayLiteral("DJ"), QByteArrayLiteral("DJI"), {"ERI", "ETH", "SOM"}};
    list.insert(QByteArrayLiteral("DJ"), cell);
    list.insert(QByteArrayLiteral("DJI"), cell);
    list.insert(QByteArrayLiteral("Republic of Djibouti"), cell);
    list.insert(QByteArrayLiteral("Djibouti"), cell);

    cell = new CountryCell {QByteArrayLiteral("Commonwealth of Dominica"), QByteArrayLiteral("Dominica"), QByteArrayLiteral("DM"), QByteArrayLiteral("DMA"), {}};
    list.insert(QByteArrayLiteral("DM"), cell);
    list.insert(QByteArrayLiteral("DMA"), cell);
    list.insert(QByteArrayLiteral("Commonwealth of Dominica"), cell);
    list.insert(QByteArrayLiteral("Dominica"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Denmark"), QByteArrayLiteral("Denmark"), QByteArrayLiteral("DK"), QByteArrayLiteral("DNK"), {"DEU"}};
    list.insert(QByteArrayLiteral("DK"), cell);
    list.insert(QByteArrayLiteral("DNK"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Denmark"), cell);
    list.insert(QByteArrayLiteral("Denmark"), cell);

    cell = new CountryCell {QByteArrayLiteral("Dominican Republic"), QByteArrayLiteral("Dominican Republic"), QByteArrayLiteral("DO"), QByteArrayLiteral("DOM"), {"HTI"}};
    list.insert(QByteArrayLiteral("DO"), cell);
    list.insert(QByteArrayLiteral("DOM"), cell);
    list.insert(QByteArrayLiteral("Dominican Republic"), cell);

    cell = new CountryCell {QByteArrayLiteral("People's Democratic Republic of Algeria"), QByteArrayLiteral("Algeria"), QByteArrayLiteral("DZ"), QByteArrayLiteral("DZA"), {"TUN", "LBY", "NER", "ESH", "MRT", "MLI", "MAR"}};
    list.insert(QByteArrayLiteral("DZ"), cell);
    list.insert(QByteArrayLiteral("DZA"), cell);
    list.insert(QByteArrayLiteral("People's Democratic Republic of Algeria"), cell);
    list.insert(QByteArrayLiteral("Algeria"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Ecuador"), QByteArrayLiteral("Ecuador"), QByteArrayLiteral("EC"), QByteArrayLiteral("ECU"), {"COL", "PER"}};
    list.insert(QByteArrayLiteral("EC"), cell);
    list.insert(QByteArrayLiteral("ECU"), cell);
    list.insert(QByteArrayLiteral("Republic of Ecuador"), cell);
    list.insert(QByteArrayLiteral("Ecuador"), cell);

    cell = new CountryCell {QByteArrayLiteral("Arab Republic of Egypt"), QByteArrayLiteral("Egypt"), QByteArrayLiteral("EG"), QByteArrayLiteral("EGY"), {"ISR", "LBY", "SDN"}};
    list.insert(QByteArrayLiteral("EG"), cell);
    list.insert(QByteArrayLiteral("EGY"), cell);
    list.insert(QByteArrayLiteral("Arab Republic of Egypt"), cell);
    list.insert(QByteArrayLiteral("Egypt"), cell);

    cell = new CountryCell {QByteArrayLiteral("State of Eritrea"), QByteArrayLiteral("Eritrea"), QByteArrayLiteral("ER"), QByteArrayLiteral("ERI"), {"DJI", "ETH", "SDN"}};
    list.insert(QByteArrayLiteral("ER"), cell);
    list.insert(QByteArrayLiteral("ERI"), cell);
    list.insert(QByteArrayLiteral("State of Eritrea"), cell);
    list.insert(QByteArrayLiteral("Eritrea"), cell);

    cell = new CountryCell {QByteArrayLiteral("Sahrawi Arab Democratic Republic"), QByteArrayLiteral("Western Sahara"), QByteArrayLiteral("EH"), QByteArrayLiteral("ESH"), {"DZA", "MRT", "MAR"}};
    list.insert(QByteArrayLiteral("EH"), cell);
    list.insert(QByteArrayLiteral("ESH"), cell);
    list.insert(QByteArrayLiteral("Sahrawi Arab Democratic Republic"), cell);
    list.insert(QByteArrayLiteral("Western Sahara"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Spain"), QByteArrayLiteral("Spain"), QByteArrayLiteral("ES"), QByteArrayLiteral("ESP"), {"AND", "FRA", "GIB", "PRT", "MAR"}};
    list.insert(QByteArrayLiteral("ES"), cell);
    list.insert(QByteArrayLiteral("ESP"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Spain"), cell);
    list.insert(QByteArrayLiteral("Spain"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Estonia"), QByteArrayLiteral("Estonia"), QByteArrayLiteral("EE"), QByteArrayLiteral("EST"), {"LVA", "RUS"}};
    list.insert(QByteArrayLiteral("EE"), cell);
    list.insert(QByteArrayLiteral("EST"), cell);
    list.insert(QByteArrayLiteral("Republic of Estonia"), cell);
    list.insert(QByteArrayLiteral("Estonia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federal Democratic Republic of Ethiopia"), QByteArrayLiteral("Ethiopia"), QByteArrayLiteral("ET"), QByteArrayLiteral("ETH"), {"DJI", "ERI", "KEN", "SOM", "SSD", "SDN"}};
    list.insert(QByteArrayLiteral("ET"), cell);
    list.insert(QByteArrayLiteral("ETH"), cell);
    list.insert(QByteArrayLiteral("Federal Democratic Republic of Ethiopia"), cell);
    list.insert(QByteArrayLiteral("Ethiopia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Finland"), QByteArrayLiteral("Finland"), QByteArrayLiteral("FI"), QByteArrayLiteral("FIN"), {"NOR", "SWE", "RUS"}};
    list.insert(QByteArrayLiteral("FI"), cell);
    list.insert(QByteArrayLiteral("FIN"), cell);
    list.insert(QByteArrayLiteral("Republic of Finland"), cell);
    list.insert(QByteArrayLiteral("Finland"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Fiji"), QByteArrayLiteral("Fiji"), QByteArrayLiteral("FJ"), QByteArrayLiteral("FJI"), {}};
    list.insert(QByteArrayLiteral("FJ"), cell);
    list.insert(QByteArrayLiteral("FJI"), cell);
    list.insert(QByteArrayLiteral("Republic of Fiji"), cell);
    list.insert(QByteArrayLiteral("Fiji"), cell);

    cell = new CountryCell {QByteArrayLiteral("Falkland Islands"), QByteArrayLiteral("Falkland Islands"), QByteArrayLiteral("FK"), QByteArrayLiteral("FLK"), {}};
    list.insert(QByteArrayLiteral("FK"), cell);
    list.insert(QByteArrayLiteral("FLK"), cell);
    list.insert(QByteArrayLiteral("Falkland Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("French Republic"), QByteArrayLiteral("France"), QByteArrayLiteral("FR"), QByteArrayLiteral("FRA"), {"AND", "BEL", "DEU", "ITA", "LUX", "MCO", "ESP", "CHE"}};
    list.insert(QByteArrayLiteral("FR"), cell);
    list.insert(QByteArrayLiteral("FRA"), cell);
    list.insert(QByteArrayLiteral("French Republic"), cell);
    list.insert(QByteArrayLiteral("France"), cell);

    cell = new CountryCell {QByteArrayLiteral("Faroe Islands"), QByteArrayLiteral("Faroe Islands"), QByteArrayLiteral("FO"), QByteArrayLiteral("FRO"), {}};
    list.insert(QByteArrayLiteral("FO"), cell);
    list.insert(QByteArrayLiteral("FRO"), cell);
    list.insert(QByteArrayLiteral("Faroe Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federated States of Micronesia"), QByteArrayLiteral("Micronesia"), QByteArrayLiteral("FM"), QByteArrayLiteral("FSM"), {}};
    list.insert(QByteArrayLiteral("FM"), cell);
    list.insert(QByteArrayLiteral("FSM"), cell);
    list.insert(QByteArrayLiteral("Federated States of Micronesia"), cell);
    list.insert(QByteArrayLiteral("Micronesia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Gabonese Republic"), QByteArrayLiteral("Gabon"), QByteArrayLiteral("GA"), QByteArrayLiteral("GAB"), {"CMR", "COG", "GNQ"}};
    list.insert(QByteArrayLiteral("GA"), cell);
    list.insert(QByteArrayLiteral("GAB"), cell);
    list.insert(QByteArrayLiteral("Gabonese Republic"), cell);
    list.insert(QByteArrayLiteral("Gabon"), cell);

    cell = new CountryCell {QByteArrayLiteral("United Kingdom of Great Britain and Northern Ireland"), QByteArrayLiteral("United Kingdom"), QByteArrayLiteral("GB"), QByteArrayLiteral("GBR"), {"IRL"}};
    list.insert(QByteArrayLiteral("GB"), cell);
    list.insert(QByteArrayLiteral("GBR"), cell);
    list.insert(QByteArrayLiteral("United Kingdom of Great Britain and Northern Ireland"), cell);
    list.insert(QByteArrayLiteral("United Kingdom"), cell);

    cell = new CountryCell {QByteArrayLiteral("Georgia"), QByteArrayLiteral("Georgia"), QByteArrayLiteral("GE"), QByteArrayLiteral("GEO"), {"ARM", "AZE", "RUS", "TUR"}};
    list.insert(QByteArrayLiteral("GE"), cell);
    list.insert(QByteArrayLiteral("GEO"), cell);
    list.insert(QByteArrayLiteral("Georgia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Bailiwick of Guernsey"), QByteArrayLiteral("Guernsey"), QByteArrayLiteral("GG"), QByteArrayLiteral("GGY"), {}};
    list.insert(QByteArrayLiteral("GG"), cell);
    list.insert(QByteArrayLiteral("GGY"), cell);
    list.insert(QByteArrayLiteral("Bailiwick of Guernsey"), cell);
    list.insert(QByteArrayLiteral("Guernsey"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Ghana"), QByteArrayLiteral("Ghana"), QByteArrayLiteral("GH"), QByteArrayLiteral("GHA"), {"BFA", "CIV", "TGO"}};
    list.insert(QByteArrayLiteral("GH"), cell);
    list.insert(QByteArrayLiteral("GHA"), cell);
    list.insert(QByteArrayLiteral("Republic of Ghana"), cell);
    list.insert(QByteArrayLiteral("Ghana"), cell);

    cell = new CountryCell {QByteArrayLiteral("Gibraltar"), QByteArrayLiteral("Gibraltar"), QByteArrayLiteral("GI"), QByteArrayLiteral("GIB"), {"ESP"}};
    list.insert(QByteArrayLiteral("GI"), cell);
    list.insert(QByteArrayLiteral("GIB"), cell);
    list.insert(QByteArrayLiteral("Gibraltar"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Guinea"), QByteArrayLiteral("Guinea"), QByteArrayLiteral("GN"), QByteArrayLiteral("GIN"), {"CIV", "GNB", "LBR", "MLI", "SEN", "SLE"}};
    list.insert(QByteArrayLiteral("GN"), cell);
    list.insert(QByteArrayLiteral("GIN"), cell);
    list.insert(QByteArrayLiteral("Republic of Guinea"), cell);
    list.insert(QByteArrayLiteral("Guinea"), cell);

    cell = new CountryCell {QByteArrayLiteral("Guadeloupe"), QByteArrayLiteral("Guadeloupe"), QByteArrayLiteral("GP"), QByteArrayLiteral("GLP"), {}};
    list.insert(QByteArrayLiteral("GP"), cell);
    list.insert(QByteArrayLiteral("GLP"), cell);
    list.insert(QByteArrayLiteral("Guadeloupe"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of the Gambia"), QByteArrayLiteral("Gambia"), QByteArrayLiteral("GM"), QByteArrayLiteral("GMB"), {"SEN"}};
    list.insert(QByteArrayLiteral("GM"), cell);
    list.insert(QByteArrayLiteral("GMB"), cell);
    list.insert(QByteArrayLiteral("Republic of the Gambia"), cell);
    list.insert(QByteArrayLiteral("Gambia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Guinea-Bissau"), QByteArrayLiteral("Guinea-Bissau"), QByteArrayLiteral("GW"), QByteArrayLiteral("GNB"), {"GIN", "SEN"}};
    list.insert(QByteArrayLiteral("GW"), cell);
    list.insert(QByteArrayLiteral("GNB"), cell);
    list.insert(QByteArrayLiteral("Republic of Guinea-Bissau"), cell);
    list.insert(QByteArrayLiteral("Guinea-Bissau"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Equatorial Guinea"), QByteArrayLiteral("Equatorial Guinea"), QByteArrayLiteral("GQ"), QByteArrayLiteral("GNQ"), {"CMR", "GAB"}};
    list.insert(QByteArrayLiteral("GQ"), cell);
    list.insert(QByteArrayLiteral("GNQ"), cell);
    list.insert(QByteArrayLiteral("Republic of Equatorial Guinea"), cell);
    list.insert(QByteArrayLiteral("Equatorial Guinea"), cell);

    cell = new CountryCell {QByteArrayLiteral("Hellenic Republic"), QByteArrayLiteral("Greece"), QByteArrayLiteral("GR"), QByteArrayLiteral("GRC"), {"ALB", "BGR", "TUR", "MKD"}};
    list.insert(QByteArrayLiteral("GR"), cell);
    list.insert(QByteArrayLiteral("GRC"), cell);
    list.insert(QByteArrayLiteral("Hellenic Republic"), cell);
    list.insert(QByteArrayLiteral("Greece"), cell);

    cell = new CountryCell {QByteArrayLiteral("Grenada"), QByteArrayLiteral("Grenada"), QByteArrayLiteral("GD"), QByteArrayLiteral("GRD"), {}};
    list.insert(QByteArrayLiteral("GD"), cell);
    list.insert(QByteArrayLiteral("GRD"), cell);
    list.insert(QByteArrayLiteral("Grenada"), cell);

    cell = new CountryCell {QByteArrayLiteral("Greenland"), QByteArrayLiteral("Greenland"), QByteArrayLiteral("GL"), QByteArrayLiteral("GRL"), {}};
    list.insert(QByteArrayLiteral("GL"), cell);
    list.insert(QByteArrayLiteral("GRL"), cell);
    list.insert(QByteArrayLiteral("Greenland"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Guatemala"), QByteArrayLiteral("Guatemala"), QByteArrayLiteral("GT"), QByteArrayLiteral("GTM"), {"BLZ", "SLV", "HND", "MEX"}};
    list.insert(QByteArrayLiteral("GT"), cell);
    list.insert(QByteArrayLiteral("GTM"), cell);
    list.insert(QByteArrayLiteral("Republic of Guatemala"), cell);
    list.insert(QByteArrayLiteral("Guatemala"), cell);

    cell = new CountryCell {QByteArrayLiteral("Guiana"), QByteArrayLiteral("French Guiana"), QByteArrayLiteral("GF"), QByteArrayLiteral("GUF"), {"BRA", "SUR"}};
    list.insert(QByteArrayLiteral("GF"), cell);
    list.insert(QByteArrayLiteral("GUF"), cell);
    list.insert(QByteArrayLiteral("Guiana"), cell);
    list.insert(QByteArrayLiteral("French Guiana"), cell);

    cell = new CountryCell {QByteArrayLiteral("Guam"), QByteArrayLiteral("Guam"), QByteArrayLiteral("GU"), QByteArrayLiteral("GUM"), {}};
    list.insert(QByteArrayLiteral("GU"), cell);
    list.insert(QByteArrayLiteral("GUM"), cell);
    list.insert(QByteArrayLiteral("Guam"), cell);

    cell = new CountryCell {QByteArrayLiteral("Co-operative Republic of Guyana"), QByteArrayLiteral("Guyana"), QByteArrayLiteral("GY"), QByteArrayLiteral("GUY"), {"BRA", "SUR", "VEN"}};
    list.insert(QByteArrayLiteral("GY"), cell);
    list.insert(QByteArrayLiteral("GUY"), cell);
    list.insert(QByteArrayLiteral("Co-operative Republic of Guyana"), cell);
    list.insert(QByteArrayLiteral("Guyana"), cell);

    cell = new CountryCell {QByteArrayLiteral("Hong Kong Special Administrative Region of the People's Republic of China"), QByteArrayLiteral("Hong Kong"), QByteArrayLiteral("HK"), QByteArrayLiteral("HKG"), {"CHN"}};
    list.insert(QByteArrayLiteral("HK"), cell);
    list.insert(QByteArrayLiteral("HKG"), cell);
    list.insert(QByteArrayLiteral("Hong Kong Special Administrative Region of the People's Republic of China"), cell);
    list.insert(QByteArrayLiteral("Hong Kong"), cell);

    cell = new CountryCell {QByteArrayLiteral("Heard Island and McDonald Islands"), QByteArrayLiteral("Heard Island and McDonald Islands"), QByteArrayLiteral("HM"), QByteArrayLiteral("HMD"), {}};
    list.insert(QByteArrayLiteral("HM"), cell);
    list.insert(QByteArrayLiteral("HMD"), cell);
    list.insert(QByteArrayLiteral("Heard Island and McDonald Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Honduras"), QByteArrayLiteral("Honduras"), QByteArrayLiteral("HN"), QByteArrayLiteral("HND"), {"GTM", "SLV", "NIC"}};
    list.insert(QByteArrayLiteral("HN"), cell);
    list.insert(QByteArrayLiteral("HND"), cell);
    list.insert(QByteArrayLiteral("Republic of Honduras"), cell);
    list.insert(QByteArrayLiteral("Honduras"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Croatia"), QByteArrayLiteral("Croatia"), QByteArrayLiteral("HR"), QByteArrayLiteral("HRV"), {"BIH", "HUN", "MNE", "SRB", "SVN"}};
    list.insert(QByteArrayLiteral("HR"), cell);
    list.insert(QByteArrayLiteral("HRV"), cell);
    list.insert(QByteArrayLiteral("Republic of Croatia"), cell);
    list.insert(QByteArrayLiteral("Croatia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Haiti"), QByteArrayLiteral("Haiti"), QByteArrayLiteral("HT"), QByteArrayLiteral("HTI"), {"DOM"}};
    list.insert(QByteArrayLiteral("HT"), cell);
    list.insert(QByteArrayLiteral("HTI"), cell);
    list.insert(QByteArrayLiteral("Republic of Haiti"), cell);
    list.insert(QByteArrayLiteral("Haiti"), cell);

    cell = new CountryCell {QByteArrayLiteral("Hungary"), QByteArrayLiteral("Hungary"), QByteArrayLiteral("HU"), QByteArrayLiteral("HUN"), {"AUT", "HRV", "ROU", "SRB", "SVK", "SVN", "UKR"}};
    list.insert(QByteArrayLiteral("HU"), cell);
    list.insert(QByteArrayLiteral("HUN"), cell);
    list.insert(QByteArrayLiteral("Hungary"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Indonesia"), QByteArrayLiteral("Indonesia"), QByteArrayLiteral("ID"), QByteArrayLiteral("IDN"), {"TLS", "MYS", "PNG"}};
    list.insert(QByteArrayLiteral("ID"), cell);
    list.insert(QByteArrayLiteral("IDN"), cell);
    list.insert(QByteArrayLiteral("Republic of Indonesia"), cell);
    list.insert(QByteArrayLiteral("Indonesia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Isle of Man"), QByteArrayLiteral("Isle of Man"), QByteArrayLiteral("IM"), QByteArrayLiteral("IMN"), {}};
    list.insert(QByteArrayLiteral("IM"), cell);
    list.insert(QByteArrayLiteral("IMN"), cell);
    list.insert(QByteArrayLiteral("Isle of Man"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of India"), QByteArrayLiteral("India"), QByteArrayLiteral("IN"), QByteArrayLiteral("IND"), {"AFG", "BGD", "BTN", "MMR", "CHN", "NPL", "PAK", "LKA"}};
    list.insert(QByteArrayLiteral("IN"), cell);
    list.insert(QByteArrayLiteral("IND"), cell);
    list.insert(QByteArrayLiteral("Republic of India"), cell);
    list.insert(QByteArrayLiteral("India"), cell);

    cell = new CountryCell {QByteArrayLiteral("British Indian Ocean Territory"), QByteArrayLiteral("British Indian Ocean Territory"), QByteArrayLiteral("IO"), QByteArrayLiteral("IOT"), {}};
    list.insert(QByteArrayLiteral("IO"), cell);
    list.insert(QByteArrayLiteral("IOT"), cell);
    list.insert(QByteArrayLiteral("British Indian Ocean Territory"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Ireland"), QByteArrayLiteral("Ireland"), QByteArrayLiteral("IE"), QByteArrayLiteral("IRL"), {"GBR"}};
    list.insert(QByteArrayLiteral("IE"), cell);
    list.insert(QByteArrayLiteral("IRL"), cell);
    list.insert(QByteArrayLiteral("Republic of Ireland"), cell);
    list.insert(QByteArrayLiteral("Ireland"), cell);

    cell = new CountryCell {QByteArrayLiteral("Islamic Republic of Iran"), QByteArrayLiteral("Iran"), QByteArrayLiteral("IR"), QByteArrayLiteral("IRN"), {"AFG", "ARM", "AZE", "IRQ", "PAK", "TUR", "TKM"}};
    list.insert(QByteArrayLiteral("IR"), cell);
    list.insert(QByteArrayLiteral("IRN"), cell);
    list.insert(QByteArrayLiteral("Islamic Republic of Iran"), cell);
    list.insert(QByteArrayLiteral("Iran"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Iraq"), QByteArrayLiteral("Iraq"), QByteArrayLiteral("IQ"), QByteArrayLiteral("IRQ"), {"IRN", "JOR", "KWT", "SAU", "SYR", "TUR"}};
    list.insert(QByteArrayLiteral("IQ"), cell);
    list.insert(QByteArrayLiteral("IRQ"), cell);
    list.insert(QByteArrayLiteral("Republic of Iraq"), cell);
    list.insert(QByteArrayLiteral("Iraq"), cell);

    cell = new CountryCell {QByteArrayLiteral("Iceland"), QByteArrayLiteral("Iceland"), QByteArrayLiteral("IS"), QByteArrayLiteral("ISL"), {}};
    list.insert(QByteArrayLiteral("IS"), cell);
    list.insert(QByteArrayLiteral("ISL"), cell);
    list.insert(QByteArrayLiteral("Iceland"), cell);

    cell = new CountryCell {QByteArrayLiteral("State of Israel"), QByteArrayLiteral("Israel"), QByteArrayLiteral("IL"), QByteArrayLiteral("ISR"), {"EGY", "JOR", "LBN", "SYR"}};
    list.insert(QByteArrayLiteral("IL"), cell);
    list.insert(QByteArrayLiteral("ISR"), cell);
    list.insert(QByteArrayLiteral("State of Israel"), cell);
    list.insert(QByteArrayLiteral("Israel"), cell);

    cell = new CountryCell {QByteArrayLiteral("Italian Republic"), QByteArrayLiteral("Italy"), QByteArrayLiteral("IT"), QByteArrayLiteral("ITA"), {"AUT", "FRA", "SMR", "SVN", "CHE", "VAT"}};
    list.insert(QByteArrayLiteral("IT"), cell);
    list.insert(QByteArrayLiteral("ITA"), cell);
    list.insert(QByteArrayLiteral("Italian Republic"), cell);
    list.insert(QByteArrayLiteral("Italy"), cell);

    cell = new CountryCell {QByteArrayLiteral("Jamaica"), QByteArrayLiteral("Jamaica"), QByteArrayLiteral("JM"), QByteArrayLiteral("JAM"), {}};
    list.insert(QByteArrayLiteral("JM"), cell);
    list.insert(QByteArrayLiteral("JAM"), cell);
    list.insert(QByteArrayLiteral("Jamaica"), cell);

    cell = new CountryCell {QByteArrayLiteral("Bailiwick of Jersey"), QByteArrayLiteral("Jersey"), QByteArrayLiteral("JE"), QByteArrayLiteral("JEY"), {}};
    list.insert(QByteArrayLiteral("JE"), cell);
    list.insert(QByteArrayLiteral("JEY"), cell);
    list.insert(QByteArrayLiteral("Bailiwick of Jersey"), cell);
    list.insert(QByteArrayLiteral("Jersey"), cell);

    cell = new CountryCell {QByteArrayLiteral("Hashemite Kingdom of Jordan"), QByteArrayLiteral("Jordan"), QByteArrayLiteral("JO"), QByteArrayLiteral("JOR"), {"IRQ", "ISR", "SAU", "SYR"}};
    list.insert(QByteArrayLiteral("JO"), cell);
    list.insert(QByteArrayLiteral("JOR"), cell);
    list.insert(QByteArrayLiteral("Hashemite Kingdom of Jordan"), cell);
    list.insert(QByteArrayLiteral("Jordan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Japan"), QByteArrayLiteral("Japan"), QByteArrayLiteral("JP"), QByteArrayLiteral("JPN"), {}};
    list.insert(QByteArrayLiteral("JP"), cell);
    list.insert(QByteArrayLiteral("JPN"), cell);
    list.insert(QByteArrayLiteral("Japan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Kazakhstan"), QByteArrayLiteral("Kazakhstan"), QByteArrayLiteral("KZ"), QByteArrayLiteral("KAZ"), {"CHN", "KGZ", "RUS", "TKM", "UZB"}};
    list.insert(QByteArrayLiteral("KZ"), cell);
    list.insert(QByteArrayLiteral("KAZ"), cell);
    list.insert(QByteArrayLiteral("Republic of Kazakhstan"), cell);
    list.insert(QByteArrayLiteral("Kazakhstan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Kenya"), QByteArrayLiteral("Kenya"), QByteArrayLiteral("KE"), QByteArrayLiteral("KEN"), {"ETH", "SOM", "SSD", "TZA", "UGA"}};
    list.insert(QByteArrayLiteral("KE"), cell);
    list.insert(QByteArrayLiteral("KEN"), cell);
    list.insert(QByteArrayLiteral("Republic of Kenya"), cell);
    list.insert(QByteArrayLiteral("Kenya"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kyrgyz Republic"), QByteArrayLiteral("Kyrgyzstan"), QByteArrayLiteral("KG"), QByteArrayLiteral("KGZ"), {"CHN", "KAZ", "TJK", "UZB"}};
    list.insert(QByteArrayLiteral("KG"), cell);
    list.insert(QByteArrayLiteral("KGZ"), cell);
    list.insert(QByteArrayLiteral("Kyrgyz Republic"), cell);
    list.insert(QByteArrayLiteral("Kyrgyzstan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Cambodia"), QByteArrayLiteral("Cambodia"), QByteArrayLiteral("KH"), QByteArrayLiteral("KHM"), {"LAO", "THA", "VNM"}};
    list.insert(QByteArrayLiteral("KH"), cell);
    list.insert(QByteArrayLiteral("KHM"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Cambodia"), cell);
    list.insert(QByteArrayLiteral("Cambodia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Independent and Sovereign Republic of Kiribati"), QByteArrayLiteral("Kiribati"), QByteArrayLiteral("KI"), QByteArrayLiteral("KIR"), {}};
    list.insert(QByteArrayLiteral("KI"), cell);
    list.insert(QByteArrayLiteral("KIR"), cell);
    list.insert(QByteArrayLiteral("Independent and Sovereign Republic of Kiribati"), cell);
    list.insert(QByteArrayLiteral("Kiribati"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federation of Saint Christopher and Nevisa"), QByteArrayLiteral("Saint Kitts and Nevis"), QByteArrayLiteral("KN"), QByteArrayLiteral("KNA"), {}};
    list.insert(QByteArrayLiteral("KN"), cell);
    list.insert(QByteArrayLiteral("KNA"), cell);
    list.insert(QByteArrayLiteral("Federation of Saint Christopher and Nevisa"), cell);
    list.insert(QByteArrayLiteral("Saint Kitts and Nevis"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Korea"), QByteArrayLiteral("South Korea"), QByteArrayLiteral("KR"), QByteArrayLiteral("KOR"), {"PRK"}};
    list.insert(QByteArrayLiteral("KR"), cell);
    list.insert(QByteArrayLiteral("KOR"), cell);
    list.insert(QByteArrayLiteral("Republic of Korea"), cell);
    list.insert(QByteArrayLiteral("South Korea"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Kosovo"), QByteArrayLiteral("Kosovo"), QByteArrayLiteral("XK"), QByteArrayLiteral("UNK"), {"ALB", "MKD", "MNE", "SRB"}};
    list.insert(QByteArrayLiteral("XK"), cell);
    list.insert(QByteArrayLiteral("UNK"), cell);
    list.insert(QByteArrayLiteral("Republic of Kosovo"), cell);
    list.insert(QByteArrayLiteral("Kosovo"), cell);

    cell = new CountryCell {QByteArrayLiteral("State of Kuwait"), QByteArrayLiteral("Kuwait"), QByteArrayLiteral("KW"), QByteArrayLiteral("KWT"), {"IRQ", "SAU"}};
    list.insert(QByteArrayLiteral("KW"), cell);
    list.insert(QByteArrayLiteral("KWT"), cell);
    list.insert(QByteArrayLiteral("State of Kuwait"), cell);
    list.insert(QByteArrayLiteral("Kuwait"), cell);

    cell = new CountryCell {QByteArrayLiteral("Lao People's Democratic Republic"), QByteArrayLiteral("Laos"), QByteArrayLiteral("LA"), QByteArrayLiteral("LAO"), {"MMR", "KHM", "CHN", "THA", "VNM"}};
    list.insert(QByteArrayLiteral("LA"), cell);
    list.insert(QByteArrayLiteral("LAO"), cell);
    list.insert(QByteArrayLiteral("Lao People's Democratic Republic"), cell);
    list.insert(QByteArrayLiteral("Laos"), cell);

    cell = new CountryCell {QByteArrayLiteral("Lebanese Republic"), QByteArrayLiteral("Lebanon"), QByteArrayLiteral("LB"), QByteArrayLiteral("LBN"), {"ISR", "SYR"}};
    list.insert(QByteArrayLiteral("LB"), cell);
    list.insert(QByteArrayLiteral("LBN"), cell);
    list.insert(QByteArrayLiteral("Lebanese Republic"), cell);
    list.insert(QByteArrayLiteral("Lebanon"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Liberia"), QByteArrayLiteral("Liberia"), QByteArrayLiteral("LR"), QByteArrayLiteral("LBR"), {"GIN", "CIV", "SLE"}};
    list.insert(QByteArrayLiteral("LR"), cell);
    list.insert(QByteArrayLiteral("LBR"), cell);
    list.insert(QByteArrayLiteral("Republic of Liberia"), cell);
    list.insert(QByteArrayLiteral("Liberia"), cell);

    cell = new CountryCell {QByteArrayLiteral("State of Libya"), QByteArrayLiteral("Libya"), QByteArrayLiteral("LY"), QByteArrayLiteral("LBY"), {"DZA", "TCD", "EGY", "NER", "SDN", "TUN"}};
    list.insert(QByteArrayLiteral("LY"), cell);
    list.insert(QByteArrayLiteral("LBY"), cell);
    list.insert(QByteArrayLiteral("State of Libya"), cell);
    list.insert(QByteArrayLiteral("Libya"), cell);

    cell = new CountryCell {QByteArrayLiteral("Saint Lucia"), QByteArrayLiteral("Saint Lucia"), QByteArrayLiteral("LC"), QByteArrayLiteral("LCA"), {}};
    list.insert(QByteArrayLiteral("LC"), cell);
    list.insert(QByteArrayLiteral("LCA"), cell);
    list.insert(QByteArrayLiteral("Saint Lucia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Principality of Liechtenstein"), QByteArrayLiteral("Liechtenstein"), QByteArrayLiteral("LI"), QByteArrayLiteral("LIE"), {"AUT", "CHE"}};
    list.insert(QByteArrayLiteral("LI"), cell);
    list.insert(QByteArrayLiteral("LIE"), cell);
    list.insert(QByteArrayLiteral("Principality of Liechtenstein"), cell);
    list.insert(QByteArrayLiteral("Liechtenstein"), cell);

    cell = new CountryCell {QByteArrayLiteral("Democratic Socialist Republic of Sri Lanka"), QByteArrayLiteral("Sri Lanka"), QByteArrayLiteral("LK"), QByteArrayLiteral("LKA"), {"IND"}};
    list.insert(QByteArrayLiteral("LK"), cell);
    list.insert(QByteArrayLiteral("LKA"), cell);
    list.insert(QByteArrayLiteral("Democratic Socialist Republic of Sri Lanka"), cell);
    list.insert(QByteArrayLiteral("Sri Lanka"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Lesotho"), QByteArrayLiteral("Lesotho"), QByteArrayLiteral("LS"), QByteArrayLiteral("LSO"), {"ZAF"}};
    list.insert(QByteArrayLiteral("LS"), cell);
    list.insert(QByteArrayLiteral("LSO"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Lesotho"), cell);
    list.insert(QByteArrayLiteral("Lesotho"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Lithuania"), QByteArrayLiteral("Lithuania"), QByteArrayLiteral("LT"), QByteArrayLiteral("LTU"), {"BLR", "LVA", "POL", "RUS"}};
    list.insert(QByteArrayLiteral("LT"), cell);
    list.insert(QByteArrayLiteral("LTU"), cell);
    list.insert(QByteArrayLiteral("Republic of Lithuania"), cell);
    list.insert(QByteArrayLiteral("Lithuania"), cell);

    cell = new CountryCell {QByteArrayLiteral("Grand Duchy of Luxembourg"), QByteArrayLiteral("Luxembourg"), QByteArrayLiteral("LU"), QByteArrayLiteral("LUX"), {"BEL", "FRA", "DEU"}};
    list.insert(QByteArrayLiteral("LU"), cell);
    list.insert(QByteArrayLiteral("LUX"), cell);
    list.insert(QByteArrayLiteral("Grand Duchy of Luxembourg"), cell);
    list.insert(QByteArrayLiteral("Luxembourg"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Latvia"), QByteArrayLiteral("Latvia"), QByteArrayLiteral("LV"), QByteArrayLiteral("LVA"), {"BLR", "EST", "LTU", "RUS"}};
    list.insert(QByteArrayLiteral("LV"), cell);
    list.insert(QByteArrayLiteral("LVA"), cell);
    list.insert(QByteArrayLiteral("Republic of Latvia"), cell);
    list.insert(QByteArrayLiteral("Latvia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Macao Special Administrative Region of the People's Republic of China"), QByteArrayLiteral("Macau"), QByteArrayLiteral("MO"), QByteArrayLiteral("MAC"), {"CHN"}};
    list.insert(QByteArrayLiteral("MO"), cell);
    list.insert(QByteArrayLiteral("MAC"), cell);
    list.insert(QByteArrayLiteral("Macao Special Administrative Region of the People's Republic of China"), cell);
    list.insert(QByteArrayLiteral("Macau"), cell);

    cell = new CountryCell {QByteArrayLiteral("Saint Martin"), QByteArrayLiteral("Saint Martin"), QByteArrayLiteral("MF"), QByteArrayLiteral("MAF"), {"SXM"}};
    list.insert(QByteArrayLiteral("MF"), cell);
    list.insert(QByteArrayLiteral("MAF"), cell);
    list.insert(QByteArrayLiteral("Saint Martin"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Morocco"), QByteArrayLiteral("Morocco"), QByteArrayLiteral("MA"), QByteArrayLiteral("MAR"), {"DZA", "ESH", "ESP"}};
    list.insert(QByteArrayLiteral("MA"), cell);
    list.insert(QByteArrayLiteral("MAR"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Morocco"), cell);
    list.insert(QByteArrayLiteral("Morocco"), cell);

    cell = new CountryCell {QByteArrayLiteral("Principality of Monaco"), QByteArrayLiteral("Monaco"), QByteArrayLiteral("MC"), QByteArrayLiteral("MCO"), {"FRA"}};
    list.insert(QByteArrayLiteral("MC"), cell);
    list.insert(QByteArrayLiteral("MCO"), cell);
    list.insert(QByteArrayLiteral("Principality of Monaco"), cell);
    list.insert(QByteArrayLiteral("Monaco"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Moldova"), QByteArrayLiteral("Moldova"), QByteArrayLiteral("MD"), QByteArrayLiteral("MDA"), {"ROU", "UKR"}};
    list.insert(QByteArrayLiteral("MD"), cell);
    list.insert(QByteArrayLiteral("MDA"), cell);
    list.insert(QByteArrayLiteral("Republic of Moldova"), cell);
    list.insert(QByteArrayLiteral("Moldova"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Madagascar"), QByteArrayLiteral("Madagascar"), QByteArrayLiteral("MG"), QByteArrayLiteral("MDG"), {}};
    list.insert(QByteArrayLiteral("MG"), cell);
    list.insert(QByteArrayLiteral("MDG"), cell);
    list.insert(QByteArrayLiteral("Republic of Madagascar"), cell);
    list.insert(QByteArrayLiteral("Madagascar"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of the Maldives"), QByteArrayLiteral("Maldives"), QByteArrayLiteral("MV"), QByteArrayLiteral("MDV"), {}};
    list.insert(QByteArrayLiteral("MV"), cell);
    list.insert(QByteArrayLiteral("MDV"), cell);
    list.insert(QByteArrayLiteral("Republic of the Maldives"), cell);
    list.insert(QByteArrayLiteral("Maldives"), cell);

    cell = new CountryCell {QByteArrayLiteral("United Mexican States"), QByteArrayLiteral("Mexico"), QByteArrayLiteral("MX"), QByteArrayLiteral("MEX"), {"BLZ", "GTM", "USA"}};
    list.insert(QByteArrayLiteral("MX"), cell);
    list.insert(QByteArrayLiteral("MEX"), cell);
    list.insert(QByteArrayLiteral("United Mexican States"), cell);
    list.insert(QByteArrayLiteral("Mexico"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of the Marshall Islands"), QByteArrayLiteral("Marshall Islands"), QByteArrayLiteral("MH"), QByteArrayLiteral("MHL"), {}};
    list.insert(QByteArrayLiteral("MH"), cell);
    list.insert(QByteArrayLiteral("MHL"), cell);
    list.insert(QByteArrayLiteral("Republic of the Marshall Islands"), cell);
    list.insert(QByteArrayLiteral("Marshall Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Macedonia"), QByteArrayLiteral("Macedonia"), QByteArrayLiteral("MK"), QByteArrayLiteral("MKD"), {"ALB", "BGR", "GRC", "UNK", "SRB"}};
    list.insert(QByteArrayLiteral("MK"), cell);
    list.insert(QByteArrayLiteral("MKD"), cell);
    list.insert(QByteArrayLiteral("Republic of Macedonia"), cell);
    list.insert(QByteArrayLiteral("Macedonia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Mali"), QByteArrayLiteral("Mali"), QByteArrayLiteral("ML"), QByteArrayLiteral("MLI"), {"DZA", "BFA", "GIN", "CIV", "MRT", "NER", "SEN"}};
    list.insert(QByteArrayLiteral("ML"), cell);
    list.insert(QByteArrayLiteral("MLI"), cell);
    list.insert(QByteArrayLiteral("Republic of Mali"), cell);
    list.insert(QByteArrayLiteral("Mali"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Malta"), QByteArrayLiteral("Malta"), QByteArrayLiteral("MT"), QByteArrayLiteral("MLT"), {}};
    list.insert(QByteArrayLiteral("MT"), cell);
    list.insert(QByteArrayLiteral("MLT"), cell);
    list.insert(QByteArrayLiteral("Republic of Malta"), cell);
    list.insert(QByteArrayLiteral("Malta"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of the Union of Myanmar"), QByteArrayLiteral("Myanmar"), QByteArrayLiteral("MM"), QByteArrayLiteral("MMR"), {"BGD", "CHN", "IND", "LAO", "THA"}};
    list.insert(QByteArrayLiteral("MM"), cell);
    list.insert(QByteArrayLiteral("MMR"), cell);
    list.insert(QByteArrayLiteral("Republic of the Union of Myanmar"), cell);
    list.insert(QByteArrayLiteral("Myanmar"), cell);

    cell = new CountryCell {QByteArrayLiteral("Montenegro"), QByteArrayLiteral("Montenegro"), QByteArrayLiteral("ME"), QByteArrayLiteral("MNE"), {"ALB", "BIH", "HRV", "UNK", "SRB"}};
    list.insert(QByteArrayLiteral("ME"), cell);
    list.insert(QByteArrayLiteral("MNE"), cell);
    list.insert(QByteArrayLiteral("Montenegro"), cell);

    cell = new CountryCell {QByteArrayLiteral("Mongolia"), QByteArrayLiteral("Mongolia"), QByteArrayLiteral("MN"), QByteArrayLiteral("MNG"), {"CHN", "RUS"}};
    list.insert(QByteArrayLiteral("MN"), cell);
    list.insert(QByteArrayLiteral("MNG"), cell);
    list.insert(QByteArrayLiteral("Mongolia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Commonwealth of the Northern Mariana Islands"), QByteArrayLiteral("Northern Mariana Islands"), QByteArrayLiteral("MP"), QByteArrayLiteral("MNP"), {}};
    list.insert(QByteArrayLiteral("MP"), cell);
    list.insert(QByteArrayLiteral("MNP"), cell);
    list.insert(QByteArrayLiteral("Commonwealth of the Northern Mariana Islands"), cell);
    list.insert(QByteArrayLiteral("Northern Mariana Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Mozambique"), QByteArrayLiteral("Mozambique"), QByteArrayLiteral("MZ"), QByteArrayLiteral("MOZ"), {"MWI", "ZAF", "SWZ", "TZA", "ZMB", "ZWE"}};
    list.insert(QByteArrayLiteral("MZ"), cell);
    list.insert(QByteArrayLiteral("MOZ"), cell);
    list.insert(QByteArrayLiteral("Republic of Mozambique"), cell);
    list.insert(QByteArrayLiteral("Mozambique"), cell);

    cell = new CountryCell {QByteArrayLiteral("Islamic Republic of Mauritania"), QByteArrayLiteral("Mauritania"), QByteArrayLiteral("MR"), QByteArrayLiteral("MRT"), {"DZA", "MLI", "SEN", "ESH"}};
    list.insert(QByteArrayLiteral("MR"), cell);
    list.insert(QByteArrayLiteral("MRT"), cell);
    list.insert(QByteArrayLiteral("Islamic Republic of Mauritania"), cell);
    list.insert(QByteArrayLiteral("Mauritania"), cell);

    cell = new CountryCell {QByteArrayLiteral("Montserrat"), QByteArrayLiteral("Montserrat"), QByteArrayLiteral("MS"), QByteArrayLiteral("MSR"), {}};
    list.insert(QByteArrayLiteral("MS"), cell);
    list.insert(QByteArrayLiteral("MSR"), cell);
    list.insert(QByteArrayLiteral("Montserrat"), cell);

    cell = new CountryCell {QByteArrayLiteral("Martinique"), QByteArrayLiteral("Martinique"), QByteArrayLiteral("MQ"), QByteArrayLiteral("MTQ"), {}};
    list.insert(QByteArrayLiteral("MQ"), cell);
    list.insert(QByteArrayLiteral("MTQ"), cell);
    list.insert(QByteArrayLiteral("Martinique"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Mauritius"), QByteArrayLiteral("Mauritius"), QByteArrayLiteral("MU"), QByteArrayLiteral("MUS"), {}};
    list.insert(QByteArrayLiteral("MU"), cell);
    list.insert(QByteArrayLiteral("MUS"), cell);
    list.insert(QByteArrayLiteral("Republic of Mauritius"), cell);
    list.insert(QByteArrayLiteral("Mauritius"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Malawi"), QByteArrayLiteral("Malawi"), QByteArrayLiteral("MW"), QByteArrayLiteral("MWI"), {"MOZ", "TZA", "ZMB"}};
    list.insert(QByteArrayLiteral("MW"), cell);
    list.insert(QByteArrayLiteral("MWI"), cell);
    list.insert(QByteArrayLiteral("Republic of Malawi"), cell);
    list.insert(QByteArrayLiteral("Malawi"), cell);

    cell = new CountryCell {QByteArrayLiteral("Malaysia"), QByteArrayLiteral("Malaysia"), QByteArrayLiteral("MY"), QByteArrayLiteral("MYS"), {"BRN", "IDN", "THA"}};
    list.insert(QByteArrayLiteral("MY"), cell);
    list.insert(QByteArrayLiteral("MYS"), cell);
    list.insert(QByteArrayLiteral("Malaysia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Department of Mayotte"), QByteArrayLiteral("Mayotte"), QByteArrayLiteral("YT"), QByteArrayLiteral("MYT"), {}};
    list.insert(QByteArrayLiteral("YT"), cell);
    list.insert(QByteArrayLiteral("MYT"), cell);
    list.insert(QByteArrayLiteral("Department of Mayotte"), cell);
    list.insert(QByteArrayLiteral("Mayotte"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Namibia"), QByteArrayLiteral("Namibia"), QByteArrayLiteral("NA"), QByteArrayLiteral("NAM"), {"AGO", "BWA", "ZAF", "ZMB"}};
    list.insert(QByteArrayLiteral("NA"), cell);
    list.insert(QByteArrayLiteral("NAM"), cell);
    list.insert(QByteArrayLiteral("Republic of Namibia"), cell);
    list.insert(QByteArrayLiteral("Namibia"), cell);

    cell = new CountryCell {QByteArrayLiteral("New Caledonia"), QByteArrayLiteral("New Caledonia"), QByteArrayLiteral("NC"), QByteArrayLiteral("NCL"), {}};
    list.insert(QByteArrayLiteral("NC"), cell);
    list.insert(QByteArrayLiteral("NCL"), cell);
    list.insert(QByteArrayLiteral("New Caledonia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Niger"), QByteArrayLiteral("Niger"), QByteArrayLiteral("NE"), QByteArrayLiteral("NER"), {"DZA", "BEN", "BFA", "TCD", "LBY", "MLI", "NGA"}};
    list.insert(QByteArrayLiteral("NE"), cell);
    list.insert(QByteArrayLiteral("NER"), cell);
    list.insert(QByteArrayLiteral("Republic of Niger"), cell);
    list.insert(QByteArrayLiteral("Niger"), cell);

    cell = new CountryCell {QByteArrayLiteral("Territory of Norfolk Island"), QByteArrayLiteral("Norfolk Island"), QByteArrayLiteral("NF"), QByteArrayLiteral("NFK"), {}};
    list.insert(QByteArrayLiteral("NF"), cell);
    list.insert(QByteArrayLiteral("NFK"), cell);
    list.insert(QByteArrayLiteral("Territory of Norfolk Island"), cell);
    list.insert(QByteArrayLiteral("Norfolk Island"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federal Republic of Nigeria"), QByteArrayLiteral("Nigeria"), QByteArrayLiteral("NG"), QByteArrayLiteral("NGA"), {"BEN", "CMR", "TCD", "NER"}};
    list.insert(QByteArrayLiteral("NG"), cell);
    list.insert(QByteArrayLiteral("NGA"), cell);
    list.insert(QByteArrayLiteral("Federal Republic of Nigeria"), cell);
    list.insert(QByteArrayLiteral("Nigeria"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Nicaragua"), QByteArrayLiteral("Nicaragua"), QByteArrayLiteral("NI"), QByteArrayLiteral("NIC"), {"CRI", "HND"}};
    list.insert(QByteArrayLiteral("NI"), cell);
    list.insert(QByteArrayLiteral("NIC"), cell);
    list.insert(QByteArrayLiteral("Republic of Nicaragua"), cell);
    list.insert(QByteArrayLiteral("Nicaragua"), cell);

    cell = new CountryCell {QByteArrayLiteral("Niue"), QByteArrayLiteral("Niue"), QByteArrayLiteral("NU"), QByteArrayLiteral("NIU"), {}};
    list.insert(QByteArrayLiteral("NU"), cell);
    list.insert(QByteArrayLiteral("NIU"), cell);
    list.insert(QByteArrayLiteral("Niue"), cell);

    cell = new CountryCell {QByteArrayLiteral("Netherlands"), QByteArrayLiteral("Netherlands"), QByteArrayLiteral("NL"), QByteArrayLiteral("NLD"), {"BEL", "DEU"}};
    list.insert(QByteArrayLiteral("NL"), cell);
    list.insert(QByteArrayLiteral("NLD"), cell);
    list.insert(QByteArrayLiteral("Netherlands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Norway"), QByteArrayLiteral("Norway"), QByteArrayLiteral("NO"), QByteArrayLiteral("NOR"), {"FIN", "SWE", "RUS"}};
    list.insert(QByteArrayLiteral("NO"), cell);
    list.insert(QByteArrayLiteral("NOR"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Norway"), cell);
    list.insert(QByteArrayLiteral("Norway"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federal Democratic Republic of Nepal"), QByteArrayLiteral("Nepal"), QByteArrayLiteral("NP"), QByteArrayLiteral("NPL"), {"CHN", "IND"}};
    list.insert(QByteArrayLiteral("NP"), cell);
    list.insert(QByteArrayLiteral("NPL"), cell);
    list.insert(QByteArrayLiteral("Federal Democratic Republic of Nepal"), cell);
    list.insert(QByteArrayLiteral("Nepal"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Nauru"), QByteArrayLiteral("Nauru"), QByteArrayLiteral("NR"), QByteArrayLiteral("NRU"), {}};
    list.insert(QByteArrayLiteral("NR"), cell);
    list.insert(QByteArrayLiteral("NRU"), cell);
    list.insert(QByteArrayLiteral("Republic of Nauru"), cell);
    list.insert(QByteArrayLiteral("Nauru"), cell);

    cell = new CountryCell {QByteArrayLiteral("New Zealand"), QByteArrayLiteral("New Zealand"), QByteArrayLiteral("NZ"), QByteArrayLiteral("NZL"), {}};
    list.insert(QByteArrayLiteral("NZ"), cell);
    list.insert(QByteArrayLiteral("NZL"), cell);
    list.insert(QByteArrayLiteral("New Zealand"), cell);

    cell = new CountryCell {QByteArrayLiteral("Sultanate of Oman"), QByteArrayLiteral("Oman"), QByteArrayLiteral("OM"), QByteArrayLiteral("OMN"), {"SAU", "ARE", "YEM"}};
    list.insert(QByteArrayLiteral("OM"), cell);
    list.insert(QByteArrayLiteral("OMN"), cell);
    list.insert(QByteArrayLiteral("Sultanate of Oman"), cell);
    list.insert(QByteArrayLiteral("Oman"), cell);

    cell = new CountryCell {QByteArrayLiteral("Islamic Republic of Pakistan"), QByteArrayLiteral("Pakistan"), QByteArrayLiteral("PK"), QByteArrayLiteral("PAK"), {"AFG", "CHN", "IND", "IRN"}};
    list.insert(QByteArrayLiteral("PK"), cell);
    list.insert(QByteArrayLiteral("PAK"), cell);
    list.insert(QByteArrayLiteral("Islamic Republic of Pakistan"), cell);
    list.insert(QByteArrayLiteral("Pakistan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Panama"), QByteArrayLiteral("Panama"), QByteArrayLiteral("PA"), QByteArrayLiteral("PAN"), {"COL", "CRI"}};
    list.insert(QByteArrayLiteral("PA"), cell);
    list.insert(QByteArrayLiteral("PAN"), cell);
    list.insert(QByteArrayLiteral("Republic of Panama"), cell);
    list.insert(QByteArrayLiteral("Panama"), cell);

    cell = new CountryCell {QByteArrayLiteral("Pitcairn Group of Islands"), QByteArrayLiteral("Pitcairn Islands"), QByteArrayLiteral("PN"), QByteArrayLiteral("PCN"), {}};
    list.insert(QByteArrayLiteral("PN"), cell);
    list.insert(QByteArrayLiteral("PCN"), cell);
    list.insert(QByteArrayLiteral("Pitcairn Group of Islands"), cell);
    list.insert(QByteArrayLiteral("Pitcairn Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Peru"), QByteArrayLiteral("Peru"), QByteArrayLiteral("PE"), QByteArrayLiteral("PER"), {"BOL", "BRA", "CHL", "COL", "ECU"}};
    list.insert(QByteArrayLiteral("PE"), cell);
    list.insert(QByteArrayLiteral("PER"), cell);
    list.insert(QByteArrayLiteral("Republic of Peru"), cell);
    list.insert(QByteArrayLiteral("Peru"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of the Philippines"), QByteArrayLiteral("Philippines"), QByteArrayLiteral("PH"), QByteArrayLiteral("PHL"), {}};
    list.insert(QByteArrayLiteral("PH"), cell);
    list.insert(QByteArrayLiteral("PHL"), cell);
    list.insert(QByteArrayLiteral("Republic of the Philippines"), cell);
    list.insert(QByteArrayLiteral("Philippines"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Palau"), QByteArrayLiteral("Palau"), QByteArrayLiteral("PW"), QByteArrayLiteral("PLW"), {}};
    list.insert(QByteArrayLiteral("PW"), cell);
    list.insert(QByteArrayLiteral("PLW"), cell);
    list.insert(QByteArrayLiteral("Republic of Palau"), cell);
    list.insert(QByteArrayLiteral("Palau"), cell);

    cell = new CountryCell {QByteArrayLiteral("Independent State of Papua New Guinea"), QByteArrayLiteral("Papua New Guinea"), QByteArrayLiteral("PG"), QByteArrayLiteral("PNG"), {"IDN"}};
    list.insert(QByteArrayLiteral("PG"), cell);
    list.insert(QByteArrayLiteral("PNG"), cell);
    list.insert(QByteArrayLiteral("Independent State of Papua New Guinea"), cell);
    list.insert(QByteArrayLiteral("Papua New Guinea"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Poland"), QByteArrayLiteral("Poland"), QByteArrayLiteral("PL"), QByteArrayLiteral("POL"), {"BLR", "CZE", "DEU", "LTU", "RUS", "SVK", "UKR"}};
    list.insert(QByteArrayLiteral("PL"), cell);
    list.insert(QByteArrayLiteral("POL"), cell);
    list.insert(QByteArrayLiteral("Republic of Poland"), cell);
    list.insert(QByteArrayLiteral("Poland"), cell);

    cell = new CountryCell {QByteArrayLiteral("Commonwealth of Puerto Rico"), QByteArrayLiteral("Puerto Rico"), QByteArrayLiteral("PR"), QByteArrayLiteral("PRI"), {}};
    list.insert(QByteArrayLiteral("PR"), cell);
    list.insert(QByteArrayLiteral("PRI"), cell);
    list.insert(QByteArrayLiteral("Commonwealth of Puerto Rico"), cell);
    list.insert(QByteArrayLiteral("Puerto Rico"), cell);

    cell = new CountryCell {QByteArrayLiteral("Democratic People's Republic of Korea"), QByteArrayLiteral("North Korea"), QByteArrayLiteral("KP"), QByteArrayLiteral("PRK"), {"CHN", "KOR", "RUS"}};
    list.insert(QByteArrayLiteral("KP"), cell);
    list.insert(QByteArrayLiteral("PRK"), cell);
    list.insert(QByteArrayLiteral("Democratic People's Republic of Korea"), cell);
    list.insert(QByteArrayLiteral("North Korea"), cell);

    cell = new CountryCell {QByteArrayLiteral("Portuguese Republic"), QByteArrayLiteral("Portugal"), QByteArrayLiteral("PT"), QByteArrayLiteral("PRT"), {"ESP"}};
    list.insert(QByteArrayLiteral("PT"), cell);
    list.insert(QByteArrayLiteral("PRT"), cell);
    list.insert(QByteArrayLiteral("Portuguese Republic"), cell);
    list.insert(QByteArrayLiteral("Portugal"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Paraguay"), QByteArrayLiteral("Paraguay"), QByteArrayLiteral("PY"), QByteArrayLiteral("PRY"), {"ARG", "BOL", "BRA"}};
    list.insert(QByteArrayLiteral("PY"), cell);
    list.insert(QByteArrayLiteral("PRY"), cell);
    list.insert(QByteArrayLiteral("Republic of Paraguay"), cell);
    list.insert(QByteArrayLiteral("Paraguay"), cell);

    cell = new CountryCell {QByteArrayLiteral("State of Palestine"), QByteArrayLiteral("Palestine"), QByteArrayLiteral("PS"), QByteArrayLiteral("PSE"), {"ISR", "EGY", "JOR"}};
    list.insert(QByteArrayLiteral("PS"), cell);
    list.insert(QByteArrayLiteral("PSE"), cell);
    list.insert(QByteArrayLiteral("State of Palestine"), cell);
    list.insert(QByteArrayLiteral("Palestine"), cell);

    cell = new CountryCell {QByteArrayLiteral("French Polynesia"), QByteArrayLiteral("French Polynesia"), QByteArrayLiteral("PF"), QByteArrayLiteral("PYF"), {}};
    list.insert(QByteArrayLiteral("PF"), cell);
    list.insert(QByteArrayLiteral("PYF"), cell);
    list.insert(QByteArrayLiteral("French Polynesia"), cell);

    cell = new CountryCell {QByteArrayLiteral("State of Qatar"), QByteArrayLiteral("Qatar"), QByteArrayLiteral("QA"), QByteArrayLiteral("QAT"), {"SAU"}};
    list.insert(QByteArrayLiteral("QA"), cell);
    list.insert(QByteArrayLiteral("QAT"), cell);
    list.insert(QByteArrayLiteral("State of Qatar"), cell);
    list.insert(QByteArrayLiteral("Qatar"), cell);

    cell = new CountryCell {QByteArrayLiteral("Reunion Island"), QByteArrayLiteral("Reunion"), QByteArrayLiteral("RE"), QByteArrayLiteral("REU"), {}};
    list.insert(QByteArrayLiteral("RE"), cell);
    list.insert(QByteArrayLiteral("REU"), cell);
    list.insert(QByteArrayLiteral("Reunion Island"), cell);
    list.insert(QByteArrayLiteral("Reunion"), cell);

    cell = new CountryCell {QByteArrayLiteral("Romania"), QByteArrayLiteral("Romania"), QByteArrayLiteral("RO"), QByteArrayLiteral("ROU"), {"BGR", "HUN", "MDA", "SRB", "UKR"}};
    list.insert(QByteArrayLiteral("RO"), cell);
    list.insert(QByteArrayLiteral("ROU"), cell);
    list.insert(QByteArrayLiteral("Romania"), cell);

    cell = new CountryCell {QByteArrayLiteral("Russian Federation"), QByteArrayLiteral("Russia"), QByteArrayLiteral("RU"), QByteArrayLiteral("RUS"), {"AZE", "BLR", "CHN", "EST", "FIN", "GEO", "KAZ", "PRK", "LVA", "LTU", "MNG", "NOR", "POL", "UKR"}};
    list.insert(QByteArrayLiteral("RU"), cell);
    list.insert(QByteArrayLiteral("RUS"), cell);
    list.insert(QByteArrayLiteral("Russian Federation"), cell);
    list.insert(QByteArrayLiteral("Russia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Rwanda"), QByteArrayLiteral("Rwanda"), QByteArrayLiteral("RW"), QByteArrayLiteral("RWA"), {"BDI", "COD", "TZA", "UGA"}};
    list.insert(QByteArrayLiteral("RW"), cell);
    list.insert(QByteArrayLiteral("RWA"), cell);
    list.insert(QByteArrayLiteral("Republic of Rwanda"), cell);
    list.insert(QByteArrayLiteral("Rwanda"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Saudi Arabia"), QByteArrayLiteral("Saudi Arabia"), QByteArrayLiteral("SA"), QByteArrayLiteral("SAU"), {"IRQ", "JOR", "KWT", "OMN", "QAT", "ARE", "YEM"}};
    list.insert(QByteArrayLiteral("SA"), cell);
    list.insert(QByteArrayLiteral("SAU"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Saudi Arabia"), cell);
    list.insert(QByteArrayLiteral("Saudi Arabia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of the Sudan"), QByteArrayLiteral("Sudan"), QByteArrayLiteral("SD"), QByteArrayLiteral("SDN"), {"CAF", "TCD", "EGY", "ERI", "ETH", "LBY", "SSD"}};
    list.insert(QByteArrayLiteral("SD"), cell);
    list.insert(QByteArrayLiteral("SDN"), cell);
    list.insert(QByteArrayLiteral("Republic of the Sudan"), cell);
    list.insert(QByteArrayLiteral("Sudan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Senegal"), QByteArrayLiteral("Senegal"), QByteArrayLiteral("SN"), QByteArrayLiteral("SEN"), {"GMB", "GIN", "GNB", "MLI", "MRT"}};
    list.insert(QByteArrayLiteral("SN"), cell);
    list.insert(QByteArrayLiteral("SEN"), cell);
    list.insert(QByteArrayLiteral("Republic of Senegal"), cell);
    list.insert(QByteArrayLiteral("Senegal"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Singapore"), QByteArrayLiteral("Singapore"), QByteArrayLiteral("SG"), QByteArrayLiteral("SGP"), {}};
    list.insert(QByteArrayLiteral("SG"), cell);
    list.insert(QByteArrayLiteral("SGP"), cell);
    list.insert(QByteArrayLiteral("Republic of Singapore"), cell);
    list.insert(QByteArrayLiteral("Singapore"), cell);

    cell = new CountryCell {QByteArrayLiteral("South Georgia and the South Sandwich Islands"), QByteArrayLiteral("South Georgia"), QByteArrayLiteral("GS"), QByteArrayLiteral("SGS"), {}};
    list.insert(QByteArrayLiteral("GS"), cell);
    list.insert(QByteArrayLiteral("SGS"), cell);
    list.insert(QByteArrayLiteral("South Georgia and the South Sandwich Islands"), cell);
    list.insert(QByteArrayLiteral("South Georgia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Svalbard og Jan Mayen"), QByteArrayLiteral("Svalbard and Jan Mayen"), QByteArrayLiteral("SJ"), QByteArrayLiteral("SJM"), {}};
    list.insert(QByteArrayLiteral("SJ"), cell);
    list.insert(QByteArrayLiteral("SJM"), cell);
    list.insert(QByteArrayLiteral("Svalbard og Jan Mayen"), cell);
    list.insert(QByteArrayLiteral("Svalbard and Jan Mayen"), cell);

    cell = new CountryCell {QByteArrayLiteral("Solomon Islands"), QByteArrayLiteral("Solomon Islands"), QByteArrayLiteral("SB"), QByteArrayLiteral("SLB"), {}};
    list.insert(QByteArrayLiteral("SB"), cell);
    list.insert(QByteArrayLiteral("SLB"), cell);
    list.insert(QByteArrayLiteral("Solomon Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Sierra Leone"), QByteArrayLiteral("Sierra Leone"), QByteArrayLiteral("SL"), QByteArrayLiteral("SLE"), {"GIN", "LBR"}};
    list.insert(QByteArrayLiteral("SL"), cell);
    list.insert(QByteArrayLiteral("SLE"), cell);
    list.insert(QByteArrayLiteral("Republic of Sierra Leone"), cell);
    list.insert(QByteArrayLiteral("Sierra Leone"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of El Salvador"), QByteArrayLiteral("El Salvador"), QByteArrayLiteral("SV"), QByteArrayLiteral("SLV"), {"GTM", "HND"}};
    list.insert(QByteArrayLiteral("SV"), cell);
    list.insert(QByteArrayLiteral("SLV"), cell);
    list.insert(QByteArrayLiteral("Republic of El Salvador"), cell);
    list.insert(QByteArrayLiteral("El Salvador"), cell);

    cell = new CountryCell {QByteArrayLiteral("Most Serene Republic of San Marino"), QByteArrayLiteral("San Marino"), QByteArrayLiteral("SM"), QByteArrayLiteral("SMR"), {"ITA"}};
    list.insert(QByteArrayLiteral("SM"), cell);
    list.insert(QByteArrayLiteral("SMR"), cell);
    list.insert(QByteArrayLiteral("Most Serene Republic of San Marino"), cell);
    list.insert(QByteArrayLiteral("San Marino"), cell);

    cell = new CountryCell {QByteArrayLiteral("Federal Republic of Somalia"), QByteArrayLiteral("Somalia"), QByteArrayLiteral("SO"), QByteArrayLiteral("SOM"), {"DJI", "ETH", "KEN"}};
    list.insert(QByteArrayLiteral("SO"), cell);
    list.insert(QByteArrayLiteral("SOM"), cell);
    list.insert(QByteArrayLiteral("Federal Republic of Somalia"), cell);
    list.insert(QByteArrayLiteral("Somalia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Saint Pierre and Miquelon"), QByteArrayLiteral("Saint Pierre and Miquelon"), QByteArrayLiteral("PM"), QByteArrayLiteral("SPM"), {}};
    list.insert(QByteArrayLiteral("PM"), cell);
    list.insert(QByteArrayLiteral("SPM"), cell);
    list.insert(QByteArrayLiteral("Saint Pierre and Miquelon"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Serbia"), QByteArrayLiteral("Serbia"), QByteArrayLiteral("RS"), QByteArrayLiteral("SRB"), {"BIH", "BGR", "HRV", "HUN", "UNK", "MKD", "MNE", "ROU"}};
    list.insert(QByteArrayLiteral("RS"), cell);
    list.insert(QByteArrayLiteral("SRB"), cell);
    list.insert(QByteArrayLiteral("Republic of Serbia"), cell);
    list.insert(QByteArrayLiteral("Serbia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of South Sudan"), QByteArrayLiteral("South Sudan"), QByteArrayLiteral("SS"), QByteArrayLiteral("SSD"), {"CAF", "COD", "ETH", "KEN", "SDN", "UGA"}};
    list.insert(QByteArrayLiteral("SS"), cell);
    list.insert(QByteArrayLiteral("SSD"), cell);
    list.insert(QByteArrayLiteral("Republic of South Sudan"), cell);
    list.insert(QByteArrayLiteral("South Sudan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Democratic Republic of Sao Tome and Principe"), QByteArrayLiteral("Sao Tome and Principe"), QByteArrayLiteral("ST"), QByteArrayLiteral("STP"), {}};
    list.insert(QByteArrayLiteral("ST"), cell);
    list.insert(QByteArrayLiteral("STP"), cell);
    list.insert(QByteArrayLiteral("Democratic Republic of Sao Tome and Principe"), cell);
    list.insert(QByteArrayLiteral("Sao Tome and Principe"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Suriname"), QByteArrayLiteral("Suriname"), QByteArrayLiteral("SR"), QByteArrayLiteral("SUR"), {"BRA", "GUF", "GUY"}};
    list.insert(QByteArrayLiteral("SR"), cell);
    list.insert(QByteArrayLiteral("SUR"), cell);
    list.insert(QByteArrayLiteral("Republic of Suriname"), cell);
    list.insert(QByteArrayLiteral("Suriname"), cell);

    cell = new CountryCell {QByteArrayLiteral("Slovak Republic"), QByteArrayLiteral("Slovakia"), QByteArrayLiteral("SK"), QByteArrayLiteral("SVK"), {"AUT", "CZE", "HUN", "POL", "UKR"}};
    list.insert(QByteArrayLiteral("SK"), cell);
    list.insert(QByteArrayLiteral("SVK"), cell);
    list.insert(QByteArrayLiteral("Slovak Republic"), cell);
    list.insert(QByteArrayLiteral("Slovakia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Slovenia"), QByteArrayLiteral("Slovenia"), QByteArrayLiteral("SI"), QByteArrayLiteral("SVN"), {"AUT", "HRV", "ITA", "HUN"}};
    list.insert(QByteArrayLiteral("SI"), cell);
    list.insert(QByteArrayLiteral("SVN"), cell);
    list.insert(QByteArrayLiteral("Republic of Slovenia"), cell);
    list.insert(QByteArrayLiteral("Slovenia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Sweden"), QByteArrayLiteral("Sweden"), QByteArrayLiteral("SE"), QByteArrayLiteral("SWE"), {"FIN", "NOR"}};
    list.insert(QByteArrayLiteral("SE"), cell);
    list.insert(QByteArrayLiteral("SWE"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Sweden"), cell);
    list.insert(QByteArrayLiteral("Sweden"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Swaziland"), QByteArrayLiteral("Swaziland"), QByteArrayLiteral("SZ"), QByteArrayLiteral("SWZ"), {"MOZ", "ZAF"}};
    list.insert(QByteArrayLiteral("SZ"), cell);
    list.insert(QByteArrayLiteral("SWZ"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Swaziland"), cell);
    list.insert(QByteArrayLiteral("Swaziland"), cell);

    cell = new CountryCell {QByteArrayLiteral("Sint Maarten"), QByteArrayLiteral("Sint Maarten"), QByteArrayLiteral("SX"), QByteArrayLiteral("SXM"), {"MAF"}};
    list.insert(QByteArrayLiteral("SX"), cell);
    list.insert(QByteArrayLiteral("SXM"), cell);
    list.insert(QByteArrayLiteral("Sint Maarten"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Seychelles"), QByteArrayLiteral("Seychelles"), QByteArrayLiteral("SC"), QByteArrayLiteral("SYC"), {}};
    list.insert(QByteArrayLiteral("SC"), cell);
    list.insert(QByteArrayLiteral("SYC"), cell);
    list.insert(QByteArrayLiteral("Republic of Seychelles"), cell);
    list.insert(QByteArrayLiteral("Seychelles"), cell);

    cell = new CountryCell {QByteArrayLiteral("Syrian Arab Republic"), QByteArrayLiteral("Syria"), QByteArrayLiteral("SY"), QByteArrayLiteral("SYR"), {"IRQ", "ISR", "JOR", "LBN", "TUR"}};
    list.insert(QByteArrayLiteral("SY"), cell);
    list.insert(QByteArrayLiteral("SYR"), cell);
    list.insert(QByteArrayLiteral("Syrian Arab Republic"), cell);
    list.insert(QByteArrayLiteral("Syria"), cell);

    cell = new CountryCell {QByteArrayLiteral("Turks and Caicos Islands"), QByteArrayLiteral("Turks and Caicos Islands"), QByteArrayLiteral("TC"), QByteArrayLiteral("TCA"), {}};
    list.insert(QByteArrayLiteral("TC"), cell);
    list.insert(QByteArrayLiteral("TCA"), cell);
    list.insert(QByteArrayLiteral("Turks and Caicos Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Chad"), QByteArrayLiteral("Chad"), QByteArrayLiteral("TD"), QByteArrayLiteral("TCD"), {"CMR", "CAF", "LBY", "NER", "NGA", "SSD"}};
    list.insert(QByteArrayLiteral("TD"), cell);
    list.insert(QByteArrayLiteral("TCD"), cell);
    list.insert(QByteArrayLiteral("Republic of Chad"), cell);
    list.insert(QByteArrayLiteral("Chad"), cell);

    cell = new CountryCell {QByteArrayLiteral("Togolese Republic"), QByteArrayLiteral("Togo"), QByteArrayLiteral("TG"), QByteArrayLiteral("TGO"), {"BEN", "BFA", "GHA"}};
    list.insert(QByteArrayLiteral("TG"), cell);
    list.insert(QByteArrayLiteral("TGO"), cell);
    list.insert(QByteArrayLiteral("Togolese Republic"), cell);
    list.insert(QByteArrayLiteral("Togo"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Thailand"), QByteArrayLiteral("Thailand"), QByteArrayLiteral("TH"), QByteArrayLiteral("THA"), {"MMR", "KHM", "LAO", "MYS"}};
    list.insert(QByteArrayLiteral("TH"), cell);
    list.insert(QByteArrayLiteral("THA"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Thailand"), cell);
    list.insert(QByteArrayLiteral("Thailand"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Tajikistan"), QByteArrayLiteral("Tajikistan"), QByteArrayLiteral("TJ"), QByteArrayLiteral("TJK"), {"AFG", "CHN", "KGZ", "UZB"}};
    list.insert(QByteArrayLiteral("TJ"), cell);
    list.insert(QByteArrayLiteral("TJK"), cell);
    list.insert(QByteArrayLiteral("Republic of Tajikistan"), cell);
    list.insert(QByteArrayLiteral("Tajikistan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Tokelau"), QByteArrayLiteral("Tokelau"), QByteArrayLiteral("TK"), QByteArrayLiteral("TKL"), {}};
    list.insert(QByteArrayLiteral("TK"), cell);
    list.insert(QByteArrayLiteral("TKL"), cell);
    list.insert(QByteArrayLiteral("Tokelau"), cell);

    cell = new CountryCell {QByteArrayLiteral("Turkmenistan"), QByteArrayLiteral("Turkmenistan"), QByteArrayLiteral("TM"), QByteArrayLiteral("TKM"), {"AFG", "IRN", "KAZ", "UZB"}};
    list.insert(QByteArrayLiteral("TM"), cell);
    list.insert(QByteArrayLiteral("TKM"), cell);
    list.insert(QByteArrayLiteral("Turkmenistan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Democratic Republic of Timor-Leste"), QByteArrayLiteral("Timor-Leste"), QByteArrayLiteral("TL"), QByteArrayLiteral("TLS"), {"IDN"}};
    list.insert(QByteArrayLiteral("TL"), cell);
    list.insert(QByteArrayLiteral("TLS"), cell);
    list.insert(QByteArrayLiteral("Democratic Republic of Timor-Leste"), cell);
    list.insert(QByteArrayLiteral("Timor-Leste"), cell);

    cell = new CountryCell {QByteArrayLiteral("Kingdom of Tonga"), QByteArrayLiteral("Tonga"), QByteArrayLiteral("TO"), QByteArrayLiteral("TON"), {}};
    list.insert(QByteArrayLiteral("TO"), cell);
    list.insert(QByteArrayLiteral("TON"), cell);
    list.insert(QByteArrayLiteral("Kingdom of Tonga"), cell);
    list.insert(QByteArrayLiteral("Tonga"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Trinidad and Tobago"), QByteArrayLiteral("Trinidad and Tobago"), QByteArrayLiteral("TT"), QByteArrayLiteral("TTO"), {}};
    list.insert(QByteArrayLiteral("TT"), cell);
    list.insert(QByteArrayLiteral("TTO"), cell);
    list.insert(QByteArrayLiteral("Republic of Trinidad and Tobago"), cell);
    list.insert(QByteArrayLiteral("Trinidad and Tobago"), cell);

    cell = new CountryCell {QByteArrayLiteral("Tunisian Republic"), QByteArrayLiteral("Tunisia"), QByteArrayLiteral("TN"), QByteArrayLiteral("TUN"), {"DZA", "LBY"}};
    list.insert(QByteArrayLiteral("TN"), cell);
    list.insert(QByteArrayLiteral("TUN"), cell);
    list.insert(QByteArrayLiteral("Tunisian Republic"), cell);
    list.insert(QByteArrayLiteral("Tunisia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Turkey"), QByteArrayLiteral("Turkey"), QByteArrayLiteral("TR"), QByteArrayLiteral("TUR"), {"ARM", "AZE", "BGR", "GEO", "GRC", "IRN", "IRQ", "SYR"}};
    list.insert(QByteArrayLiteral("TR"), cell);
    list.insert(QByteArrayLiteral("TUR"), cell);
    list.insert(QByteArrayLiteral("Republic of Turkey"), cell);
    list.insert(QByteArrayLiteral("Turkey"), cell);

    cell = new CountryCell {QByteArrayLiteral("Tuvalu"), QByteArrayLiteral("Tuvalu"), QByteArrayLiteral("TV"), QByteArrayLiteral("TUV"), {}};
    list.insert(QByteArrayLiteral("TV"), cell);
    list.insert(QByteArrayLiteral("TUV"), cell);
    list.insert(QByteArrayLiteral("Tuvalu"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of China (Taiwan)"), QByteArrayLiteral("Taiwan"), QByteArrayLiteral("TW"), QByteArrayLiteral("TWN"), {}};
    list.insert(QByteArrayLiteral("TW"), cell);
    list.insert(QByteArrayLiteral("TWN"), cell);
    list.insert(QByteArrayLiteral("Republic of China (Taiwan)"), cell);
    list.insert(QByteArrayLiteral("Taiwan"), cell);

    cell = new CountryCell {QByteArrayLiteral("United Republic of Tanzania"), QByteArrayLiteral("Tanzania"), QByteArrayLiteral("TZ"), QByteArrayLiteral("TZA"), {"BDI", "COD", "KEN", "MWI", "MOZ", "RWA", "UGA", "ZMB"}};
    list.insert(QByteArrayLiteral("TZ"), cell);
    list.insert(QByteArrayLiteral("TZA"), cell);
    list.insert(QByteArrayLiteral("United Republic of Tanzania"), cell);
    list.insert(QByteArrayLiteral("Tanzania"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Uganda"), QByteArrayLiteral("Uganda"), QByteArrayLiteral("UG"), QByteArrayLiteral("UGA"), {"COD", "KEN", "RWA", "SSD", "TZA"}};
    list.insert(QByteArrayLiteral("UG"), cell);
    list.insert(QByteArrayLiteral("UGA"), cell);
    list.insert(QByteArrayLiteral("Republic of Uganda"), cell);
    list.insert(QByteArrayLiteral("Uganda"), cell);

    cell = new CountryCell {QByteArrayLiteral("Ukraine"), QByteArrayLiteral("Ukraine"), QByteArrayLiteral("UA"), QByteArrayLiteral("UKR"), {"BLR", "HUN", "MDA", "POL", "ROU", "RUS", "SVK"}};
    list.insert(QByteArrayLiteral("UA"), cell);
    list.insert(QByteArrayLiteral("UKR"), cell);
    list.insert(QByteArrayLiteral("Ukraine"), cell);

    cell = new CountryCell {QByteArrayLiteral("United States Minor Outlying Islands"), QByteArrayLiteral("United States Minor Outlying Islands"), QByteArrayLiteral("UM"), QByteArrayLiteral("UMI"), {}};
    list.insert(QByteArrayLiteral("UM"), cell);
    list.insert(QByteArrayLiteral("UMI"), cell);
    list.insert(QByteArrayLiteral("United States Minor Outlying Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Oriental Republic of Uruguay"), QByteArrayLiteral("Uruguay"), QByteArrayLiteral("UY"), QByteArrayLiteral("URY"), {"ARG", "BRA"}};
    list.insert(QByteArrayLiteral("UY"), cell);
    list.insert(QByteArrayLiteral("URY"), cell);
    list.insert(QByteArrayLiteral("Oriental Republic of Uruguay"), cell);
    list.insert(QByteArrayLiteral("Uruguay"), cell);

    cell = new CountryCell {QByteArrayLiteral("United States of America"), QByteArrayLiteral("United States"), QByteArrayLiteral("US"), QByteArrayLiteral("USA"), {"CAN", "MEX"}};
    list.insert(QByteArrayLiteral("US"), cell);
    list.insert(QByteArrayLiteral("USA"), cell);
    list.insert(QByteArrayLiteral("United States of America"), cell);
    list.insert(QByteArrayLiteral("United States"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Uzbekistan"), QByteArrayLiteral("Uzbekistan"), QByteArrayLiteral("UZ"), QByteArrayLiteral("UZB"), {"AFG", "KAZ", "KGZ", "TJK", "TKM"}};
    list.insert(QByteArrayLiteral("UZ"), cell);
    list.insert(QByteArrayLiteral("UZB"), cell);
    list.insert(QByteArrayLiteral("Republic of Uzbekistan"), cell);
    list.insert(QByteArrayLiteral("Uzbekistan"), cell);

    cell = new CountryCell {QByteArrayLiteral("Vatican City State"), QByteArrayLiteral("Vatican City"), QByteArrayLiteral("VA"), QByteArrayLiteral("VAT"), {"ITA"}};
    list.insert(QByteArrayLiteral("VA"), cell);
    list.insert(QByteArrayLiteral("VAT"), cell);
    list.insert(QByteArrayLiteral("Vatican City State"), cell);
    list.insert(QByteArrayLiteral("Vatican City"), cell);

    cell = new CountryCell {QByteArrayLiteral("Saint Vincent and the Grenadines"), QByteArrayLiteral("Saint Vincent and the Grenadines"), QByteArrayLiteral("VC"), QByteArrayLiteral("VCT"), {}};
    list.insert(QByteArrayLiteral("VC"), cell);
    list.insert(QByteArrayLiteral("VCT"), cell);
    list.insert(QByteArrayLiteral("Saint Vincent and the Grenadines"), cell);

    cell = new CountryCell {QByteArrayLiteral("Bolivarian Republic of Venezuela"), QByteArrayLiteral("Venezuela"), QByteArrayLiteral("VE"), QByteArrayLiteral("VEN"), {"BRA", "COL", "GUY"}};
    list.insert(QByteArrayLiteral("VE"), cell);
    list.insert(QByteArrayLiteral("VEN"), cell);
    list.insert(QByteArrayLiteral("Bolivarian Republic of Venezuela"), cell);
    list.insert(QByteArrayLiteral("Venezuela"), cell);

    cell = new CountryCell {QByteArrayLiteral("Virgin Islands"), QByteArrayLiteral("British Virgin Islands"), QByteArrayLiteral("VG"), QByteArrayLiteral("VGB"), {}};
    list.insert(QByteArrayLiteral("VG"), cell);
    list.insert(QByteArrayLiteral("VGB"), cell);
    list.insert(QByteArrayLiteral("Virgin Islands"), cell);
    list.insert(QByteArrayLiteral("British Virgin Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Virgin Islands of the United States"), QByteArrayLiteral("United States Virgin Islands"), QByteArrayLiteral("VI"), QByteArrayLiteral("VIR"), {}};
    list.insert(QByteArrayLiteral("VI"), cell);
    list.insert(QByteArrayLiteral("VIR"), cell);
    list.insert(QByteArrayLiteral("Virgin Islands of the United States"), cell);
    list.insert(QByteArrayLiteral("United States Virgin Islands"), cell);

    cell = new CountryCell {QByteArrayLiteral("Socialist Republic of Vietnam"), QByteArrayLiteral("Vietnam"), QByteArrayLiteral("VN"), QByteArrayLiteral("VNM"), {"KHM", "CHN", "LAO"}};
    list.insert(QByteArrayLiteral("VN"), cell);
    list.insert(QByteArrayLiteral("VNM"), cell);
    list.insert(QByteArrayLiteral("Socialist Republic of Vietnam"), cell);
    list.insert(QByteArrayLiteral("Vietnam"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Vanuatu"), QByteArrayLiteral("Vanuatu"), QByteArrayLiteral("VU"), QByteArrayLiteral("VUT"), {}};
    list.insert(QByteArrayLiteral("VU"), cell);
    list.insert(QByteArrayLiteral("VUT"), cell);
    list.insert(QByteArrayLiteral("Republic of Vanuatu"), cell);
    list.insert(QByteArrayLiteral("Vanuatu"), cell);

    cell = new CountryCell {QByteArrayLiteral("Territory of the Wallis and Futuna Islands"), QByteArrayLiteral("Wallis and Futuna"), QByteArrayLiteral("WF"), QByteArrayLiteral("WLF"), {}};
    list.insert(QByteArrayLiteral("WF"), cell);
    list.insert(QByteArrayLiteral("WLF"), cell);
    list.insert(QByteArrayLiteral("Territory of the Wallis and Futuna Islands"), cell);
    list.insert(QByteArrayLiteral("Wallis and Futuna"), cell);

    cell = new CountryCell {QByteArrayLiteral("Independent State of Samoa"), QByteArrayLiteral("Samoa"), QByteArrayLiteral("WS"), QByteArrayLiteral("WSM"), {}};
    list.insert(QByteArrayLiteral("WS"), cell);
    list.insert(QByteArrayLiteral("WSM"), cell);
    list.insert(QByteArrayLiteral("Independent State of Samoa"), cell);
    list.insert(QByteArrayLiteral("Samoa"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Yemen"), QByteArrayLiteral("Yemen"), QByteArrayLiteral("YE"), QByteArrayLiteral("YEM"), {"OMN", "SAU"}};
    list.insert(QByteArrayLiteral("YE"), cell);
    list.insert(QByteArrayLiteral("YEM"), cell);
    list.insert(QByteArrayLiteral("Republic of Yemen"), cell);
    list.insert(QByteArrayLiteral("Yemen"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of South Africa"), QByteArrayLiteral("South Africa"), QByteArrayLiteral("ZA"), QByteArrayLiteral("ZAF"), {"BWA", "LSO", "MOZ", "NAM", "SWZ", "ZWE"}};
    list.insert(QByteArrayLiteral("ZA"), cell);
    list.insert(QByteArrayLiteral("ZAF"), cell);
    list.insert(QByteArrayLiteral("Republic of South Africa"), cell);
    list.insert(QByteArrayLiteral("South Africa"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Zambia"), QByteArrayLiteral("Zambia"), QByteArrayLiteral("ZM"), QByteArrayLiteral("ZMB"), {"AGO", "BWA", "COD", "MWI", "MOZ", "NAM", "TZA", "ZWE"}};
    list.insert(QByteArrayLiteral("ZM"), cell);
    list.insert(QByteArrayLiteral("ZMB"), cell);
    list.insert(QByteArrayLiteral("Republic of Zambia"), cell);
    list.insert(QByteArrayLiteral("Zambia"), cell);

    cell = new CountryCell {QByteArrayLiteral("Republic of Zimbabwe"), QByteArrayLiteral("Zimbabwe"), QByteArrayLiteral("ZW"), QByteArrayLiteral("ZWE"), {"BWA", "MOZ", "ZAF", "ZMB"}};
    list.insert(QByteArrayLiteral("ZW"), cell);
    list.insert(QByteArrayLiteral("ZWE"), cell);
    list.insert(QByteArrayLiteral("Republic of Zimbabwe"), cell);
    list.insert(QByteArrayLiteral("Zimbabwe"), cell);
}
