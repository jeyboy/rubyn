#ifndef ERB_PRESET
#define ERB_PRESET

#include "ihighlight_preset.h"

//KINDS_NOT_LOC = HTML::KINDS_NOT_LOC

//ERB_RUBY_BLOCK = /
//  (<%(?!%)[-=\#]?)
//  ((?>
//    [^\-%]*    # normal*
//    (?>        # special
//      (?: %(?!>) | -(?!%>) )
//      [^\-%]*  # normal*
//    )*
//  ))
//  ((?: -?%> )?)
///x  # :nodoc:

//START_OF_ERB = /
//  <%(?!%)
///x  # :nodoc:

//protected

//def setup
//  @ruby_scanner = CodeRay.scanner :ruby, :tokens => @tokens, :keep_tokens => true
//  @html_scanner = CodeRay.scanner :html, :tokens => @tokens, :keep_tokens => true, :keep_state => true
//end

//def reset_instance
//  super
//  @html_scanner.reset
//end

//def scan_tokens encoder, options

//  until eos?

//    if (match = scan_until(/(?=#{START_OF_ERB})/o) || scan_rest) and not match.empty?
//      @html_scanner.tokenize match, :tokens => encoder

//    elsif match = scan(/#{ERB_RUBY_BLOCK}/o)
//      start_tag = self[1]
//      code = self[2]
//      end_tag = self[3]

//      encoder.begin_group :inline
//      encoder.text_token start_tag, :inline_delimiter

//      if start_tag == '<%#'
//        encoder.text_token code, :comment
//      else
//        @ruby_scanner.tokenize code, :tokens => encoder
//      end unless code.empty?

//      encoder.text_token end_tag, :inline_delimiter unless end_tag.empty?
//      encoder.end_group :inline

//    else
//      raise_inspect 'else-case reached!', encoder

//    end

//  end

//  encoder

//end

//end

//end
//end

class ErbPreset : public IHighlightPreset, public SingletonPtr<ErbPreset> {
public:
    ErbPreset() {
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

#endif // ERB_PRESET
