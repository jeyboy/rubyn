#ifndef PROJECT_TREE_STYLE_H
#define PROJECT_TREE_STYLE_H

#include <qproxystyle.h>
#include <qevent.h>

class ProjectTreeStyle : public QProxyStyle {
public:
    int styleHint(StyleHint hint, const QStyleOption * option = nullptr, const QWidget * widget = nullptr, QStyleHintReturn * returnData = nullptr) const {
        if(hint == QStyle::SH_ListViewExpand_SelectMouseType)
            return QEvent::MouseButtonRelease;

        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

#endif // PROJECT_TREE_STYLE_H
