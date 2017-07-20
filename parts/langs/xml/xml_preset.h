#ifndef XML_PRESET
#define XML_PRESET

#include "ihighlight_preset.h"

//!!!!!!!!!!!!!!!!
//TODO: need to find rules

//cdata=
//  RegExp('(\&lt;|<)\\!\\[[\\w\\s]*?\\[(.|\\s)*?\\]\\](\&gt;|>)','gm')

//comments=
//  RegExp('(\&lt;|<)!--\\s*.*?\\s*--(\&gt;|>)','gm')

//?=
// RegExp('([:\\w-\.]+)\\s*=\\s*(".*?"|\'.*?\'|\\w+)*|(\\w+)','gm')

//;while((match=regex.exec(this.code))!=null)
//{if(match[1]==null)
//{continue;}
//push(this.matches,new dp.sh.Match(match[1],match.index,'attribute'));if(match[2]!=undefined)
//{push(this.matches,new dp.sh.Match(match[2],match.index+match[0].indexOf(match[2]),'attribute-value'));}}
//this.GetMatches(new RegExp('(\&lt;|<)/*\\?*(?!\\!)|/*\\?*(\&gt;|>)','gm'),'tag');regex=new RegExp('(?:\&lt;|<)/*\\?*\\s*([:\\w-\.]+)','gm');while((match=regex.exec(this.code))!=null)
//{push(this.matches,new dp.sh.Match(match[1],match.index+match[0].indexOf(match[1]),'tag-name'));}}

class XmlPreset : public IHighlightPreset, public SingletonPtr<XmlPreset> {
public:
    XmlPreset() {
        HighlightingRule rule;

//        QString keywords = "void class char volatile template typedef union unsigned virtual typename const double enum explicit friend private protected public inline short signals static struct slots signed int long namespace operator";
//        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("^\\s*#.*");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_preprocessing);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
//        highlighting_rules.append(rule);


//        highlighting_rules.append(singleQuotationRule());


//        highlighting_rules.append(doubleQuotationRule());


//        highlighting_rules.append(numbersRule());


//        rule.pattern = QRegularExpression("//[^\n]*");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
//        highlighting_rules.append(rule);

//        comment_start_expression = QRegularExpression("/\\*");
//        comment_end_expression = QRegularExpression("\\*/");
    }
};

#endif // XML_PRESET
