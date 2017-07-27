#ifndef JSON_PRESET
#define JSON_PRESET

#include "parts/highligters/ihighlight_preset.h"

/////////////////// FULL VALIDATION  ///////////////////////

//  (?(DEFINE)
//     (?<number>   -? (?= [1-9]|0(?!\d) ) \d+ (\.\d+)? ([eE] [+-]? \d+)? )
//     (?<boolean>   true | false | null )
//     (?<string>    " ([^"\\\\]* | \\\\ ["\\\\bfnrt\/] | \\\\ u [0-9a-f]{4} )* " )
//     (?<array>     \[  (?:  (?&json)  (?: , (?&json)  )*  )?  \s* \] )
//     (?<pair>      \s* (?&string) \s* : (?&json)  )
//     (?<object>    \{  (?:  (?&pair)  (?: , (?&pair)  )*  )?  \s* \} )
//     (?<json>   \s* (?: (?&number) | (?&boolean) | (?&string) | (?&array) | (?&object) ) \s* )
//  )
//  \A (?&json) \Z
//  /six

///////////////////////////////////////////////////////////






//KINDS_NOT_LOC = [
//  :float, :char, :content, :delimiter,
//  :error, :integer, :operator, :value,
//]  # :nodoc:

//ESCAPE = / [bfnrt\\"\/] /x  # :nodoc:
//UNICODE_ESCAPE = / u[a-fA-F0-9]{4} /x  # :nodoc:
//KEY = / (?> (?: [^\\"]+ | \\. )* ) " \s* : /x

//protected

//def setup
//  @state = :initial
//end

//# See http://json.org/ for a definition of the JSON lexic/grammar.
//def scan_tokens encoder, options
//  state = options[:state] || @state

//  if [:string, :key].include? state
//    encoder.begin_group state
//  end

//  until eos?

//    case state

//    when :initial
//      if match = scan(/ \s+ /x)
//        encoder.text_token match, :space
//      elsif match = scan(/"/)
//        state = check(/#{KEY}/o) ? :key : :string
//        encoder.begin_group state
//        encoder.text_token match, :delimiter
//      elsif match = scan(/ [:,\[{\]}] /x)
//        encoder.text_token match, :operator
//      elsif match = scan(/ true | false | null /x)
//        encoder.text_token match, :value
//      elsif match = scan(/ -? (?: 0 | [1-9]\d* ) /x)
//        if scan(/ \.\d+ (?:[eE][-+]?\d+)? | [eE][-+]? \d+ /x)
//          match << matched
//          encoder.text_token match, :float
//        else
//          encoder.text_token match, :integer
//        end
//      else
//        encoder.text_token getch, :error
//      end

//    when :string, :key
//      if match = scan(/[^\\"]+/)
//        encoder.text_token match, :content
//      elsif match = scan(/"/)
//        encoder.text_token match, :delimiter
//        encoder.end_group state
//        state = :initial
//      elsif match = scan(/ \\ (?: #{ESCAPE} | #{UNICODE_ESCAPE} ) /mox)
//        encoder.text_token match, :char
//      elsif match = scan(/\\./m)
//        encoder.text_token match, :content
//      elsif match = scan(/ \\ | $ /x)
//        encoder.end_group state
//        encoder.text_token match, :error unless match.empty?
//        state = :initial
//      else
//        raise_inspect "else case \" reached; %p not handled." % peek(1), encoder
//      end

//    else
//      raise_inspect 'Unknown state: %p' % [state], encoder

//    end
//  end

//  if options[:keep_state]
//    @state = state
//  end

//  if [:string, :key].include? state
//    encoder.end_group state
//  end

//  encoder
//end

//end

//end
//end


class PresetJson : public IHighlightPreset, public SingletonPtr<PresetJson> {
public:
    PresetJson() {
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

#endif // JSON_PRESET
