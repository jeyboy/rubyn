#ifndef DELPHI_PRESET
#define DELPHI_PRESET

#include "ihighlight_preset.h"


//KEYWORDS = [
//  'and', 'array', 'as', 'at', 'asm', 'at', 'begin', 'case', 'class',
//  'const', 'constructor', 'destructor', 'dispinterface', 'div', 'do',
//  'downto', 'else', 'end', 'except', 'exports', 'file', 'finalization',
//  'finally', 'for', 'function', 'goto', 'if', 'implementation', 'in',
//  'inherited', 'initialization', 'inline', 'interface', 'is', 'label',
//  'library', 'mod', 'nil', 'not', 'object', 'of', 'or', 'out', 'packed',
//  'procedure', 'program', 'property', 'raise', 'record', 'repeat',
//  'resourcestring', 'set', 'shl', 'shr', 'string', 'then', 'threadvar',
//  'to', 'try', 'type', 'unit', 'until', 'uses', 'var', 'while', 'with',
//  'xor', 'on',
//]  # :nodoc:

//DIRECTIVES = [
//  'absolute', 'abstract', 'assembler', 'at', 'automated', 'cdecl',
//  'contains', 'deprecated', 'dispid', 'dynamic', 'export',
//  'external', 'far', 'forward', 'implements', 'local',
//  'near', 'nodefault', 'on', 'overload', 'override',
//  'package', 'pascal', 'platform', 'private', 'protected', 'public',
//  'published', 'read', 'readonly', 'register', 'reintroduce',
//  'requires', 'resident', 'safecall', 'stdcall', 'stored', 'varargs',
//  'virtual', 'write', 'writeonly',
//]  # :nodoc:

//IDENT_KIND = WordList::CaseIgnoring.new(:ident).
//  add(KEYWORDS, :keyword).
//  add(DIRECTIVES, :directive)  # :nodoc:

//NAME_FOLLOWS = WordList::CaseIgnoring.new(false).
//  add(%w(procedure function .))  # :nodoc:

//protected

//def scan_tokens encoder, options

//  state = :initial
//  last_token = ''

//  until eos?

//    if state == :initial

//      if match = scan(/ \s+ /x)
//        encoder.text_token match, :space
//        next

//      elsif match = scan(%r! \{ \$ [^}]* \}? | \(\* \$ (?: .*? \*\) | .* ) !mx)
//        encoder.text_token match, :preprocessor
//        next

//      elsif match = scan(%r! // [^\n]* | \{ [^}]* \}? | \(\* (?: .*? \*\) | .* ) !mx)
//        encoder.text_token match, :comment
//        next

//      elsif match = scan(/ <[>=]? | >=? | :=? | [-+=*\/;,@\^|\(\)\[\]] | \.\. /x)
//        encoder.text_token match, :operator

//      elsif match = scan(/\./)
//        encoder.text_token match, :operator
//        next if last_token == 'end'

//      elsif match = scan(/ [A-Za-z_][A-Za-z_0-9]* /x)
//        encoder.text_token match, NAME_FOLLOWS[last_token] ? :ident : IDENT_KIND[match]

//      elsif match = skip(/ ' ( [^\n']|'' ) (?:'|$) /x)
//        encoder.begin_group :char
//        encoder.text_token "'", :delimiter
//        encoder.text_token self[1], :content
//        encoder.text_token "'", :delimiter
//        encoder.end_group :char
//        next

//      elsif match = scan(/ ' /x)
//        encoder.begin_group :string
//        encoder.text_token match, :delimiter
//        state = :string

//      elsif match = scan(/ \# (?: \d+ | \$[0-9A-Fa-f]+ ) /x)
//        encoder.text_token match, :char

//      elsif match = scan(/ \$ [0-9A-Fa-f]+ /x)
//        encoder.text_token match, :hex

//      elsif match = scan(/ (?: \d+ ) (?![eE]|\.[^.]) /x)
//        encoder.text_token match, :integer

//      elsif match = scan(/ \d+ (?: \.\d+ (?: [eE][+-]? \d+ )? | [eE][+-]? \d+ ) /x)
//        encoder.text_token match, :float

//      else
//        encoder.text_token getch, :error
//        next

//      end

//    elsif state == :string
//      if match = scan(/[^\n']+/)
//        encoder.text_token match, :content
//      elsif match = scan(/''/)
//        encoder.text_token match, :char
//      elsif match = scan(/'/)
//        encoder.text_token match, :delimiter
//        encoder.end_group :string
//        state = :initial
//        next
//      elsif match = scan(/\n/)
//        encoder.end_group :string
//        encoder.text_token match, :space
//        state = :initial
//      else
//        raise "else case \' reached; %p not handled." % peek(1), encoder
//      end

//    else
//      raise 'else-case reached', encoder

//    end

//    last_token = match

//  end

//  if state == :string
//    encoder.end_group state
//  end

//  encoder
//end

//end

//end
//end





// keywords=
//  abs addr and ansichar ansistring array as asm begin boolean byte cardinal case char class comp const constructor currency destructor div do double
//  downto else end except exports extended false file finalization finally for function goto if implementation in inherited int64 initialization integer
//  interface is label library longint longword mod nil not object of on or packed pansichar pansistring pchar pcurrency pdatetime pextended pint64 pointer
//  private procedure program property pshortstring pstring pvariant pwidechar pwidestring protected public published raise real real48 record repeat set shl
//  shortint shortstring shr single smallint string then threadvar to true try type unit until uses val var varirnt while widechar widestring with word write
//  writeln xor

// comment=
//  \\(\\*[\\s\\S]*?\\*\\)
//  {(?!\\$)[\\s\\S]*?}
//  SingleLineCComments


// RegexLib.SingleQuotedString

// directive=
//  \\{\\$[a-zA-Z]+ .+\\}

// number=
//  \\$[a-zA-Z0-9]+\\b


class DelphiPreset : public IHighlightPreset, public SingletonPtr<DelphiPreset> {
public:
    DelphiPreset() {
        HighlightingRule rule;

//        QString keywords = "void class char volatile template typedef union unsigned virtual typename const double enum explicit friend private protected public inline short signals static struct slots signed int long namespace operator";
//        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("^ *#.*");
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

#endif // DELPHI_PRESET
