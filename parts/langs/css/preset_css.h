#ifndef CSS_PRESET
#define CSS_PRESET

#include "parts/highligters/ihighlight_preset.h"


//KINDS_NOT_LOC = [
//  :comment,
//  :class, :pseudo_class, :tag,
//  :id, :directive,
//  :key, :value, :operator, :color, :float, :string,
//  :error, :important, :type,
//]  # :nodoc:

//module RE  # :nodoc:
//  Hex = /[0-9a-fA-F]/
//  Unicode = /\\#{Hex}{1,6}\b/ # differs from standard because it allows uppercase hex too
//  Escape = /#{Unicode}|\\[^\n0-9a-fA-F]/
//  NMChar = /[-_a-zA-Z0-9]/
//  NMStart = /[_a-zA-Z]/
//  String1 = /"(?:[^\n\\"]+|\\\n|#{Escape})*"?/  # TODO: buggy regexp
//  String2 = /'(?:[^\n\\']+|\\\n|#{Escape})*'?/  # TODO: buggy regexp
//  String = /#{String1}|#{String2}/

//  HexColor = /#(?:#{Hex}{6}|#{Hex}{3})/

//  Num = /-?(?:[0-9]*\.[0-9]+|[0-9]+)n?/
//  Name = /#{NMChar}+/
//  Ident = /-?#{NMStart}#{NMChar}*/
//  AtKeyword = /@#{Ident}/
//  Percentage = /#{Num}%/

//  reldimensions = %w[em ex px]
//  absdimensions = %w[in cm mm pt pc]
//  Unit = Regexp.union(*(reldimensions + absdimensions + %w[s dpi dppx deg]))

//  Dimension = /#{Num}#{Unit}/

//  Function = /(?:url|alpha|attr|counters?)\((?:[^)\n]|\\\))*\)?/

//  Id = /(?!#{HexColor}\b(?!-))##{Name}/
//  Class = /\.#{Name}/
//  PseudoClass = /::?#{Ident}/
//  AttributeSelector = /\[[^\]]*\]?/
//end

//protected

//def setup
//  @state = :initial
//  @value_expected = false
//end

//def scan_tokens encoder, options
//  states = Array(options[:state] || @state).dup
//  value_expected = @value_expected

//  until eos?

//    if match = scan(/\s+/)
//      encoder.text_token match, :space

//    elsif case states.last
//      when :initial, :media
//        if match = scan(/(?>#{RE::Ident})(?!\()|\*/ox)
//          encoder.text_token match, :tag
//          next
//        elsif match = scan(RE::Class)
//          encoder.text_token match, :class
//          next
//        elsif match = scan(RE::Id)
//          encoder.text_token match, :id
//          next
//        elsif match = scan(RE::PseudoClass)
//          encoder.text_token match, :pseudo_class
//          next
//        elsif match = scan(RE::AttributeSelector)
//          # TODO: Improve highlighting inside of attribute selectors.
//          encoder.text_token match[0,1], :operator
//          encoder.text_token match[1..-2], :attribute_name if match.size > 2
//          encoder.text_token match[-1,1], :operator if match[-1] == ?]
//          next
//        elsif match = scan(/@media/)
//          encoder.text_token match, :directive
//          states.push :media_before_name
//          next
//        end

//      when :block
//        if match = scan(/(?>#{RE::Ident})(?!\()/ox)
//          if value_expected
//            encoder.text_token match, :value
//          else
//            encoder.text_token match, :key
//          end
//          next
//        end

//      when :media_before_name
//        if match = scan(RE::Ident)
//          encoder.text_token match, :type
//          states[-1] = :media_after_name
//          next
//        end

//      when :media_after_name
//        if match = scan(/\{/)
//          encoder.text_token match, :operator
//          states[-1] = :media
//          next
//        end

//      else
//        #:nocov:
//        raise_inspect 'Unknown state', encoder
//        #:nocov:

//      end

//    elsif match = scan(/\/\*(?:.*?\*\/|\z)/m)
//      encoder.text_token match, :comment

//    elsif match = scan(/\{/)
//      value_expected = false
//      encoder.text_token match, :operator
//      states.push :block

//    elsif match = scan(/\}/)
//      value_expected = false
//      encoder.text_token match, :operator
//      if states.last == :block || states.last == :media
//        states.pop
//      end

//    elsif match = scan(/#{RE::String}/o)
//      encoder.begin_group :string
//      encoder.text_token match[0, 1], :delimiter
//      encoder.text_token match[1..-2], :content if match.size > 2
//      encoder.text_token match[-1, 1], :delimiter if match.size >= 2
//      encoder.end_group :string

//    elsif match = scan(/#{RE::Function}/o)
//      encoder.begin_group :function
//      start = match[/^\w+\(/]
//      encoder.text_token start, :delimiter
//      if match[-1] == ?)
//        encoder.text_token match[start.size..-2], :content if match.size > start.size + 1
//        encoder.text_token ')', :delimiter
//      else
//        encoder.text_token match[start.size..-1], :content if match.size > start.size
//      end
//      encoder.end_group :function

//    elsif match = scan(/(?: #{RE::Dimension} | #{RE::Percentage} | #{RE::Num} )/ox)
//      encoder.text_token match, :float

//    elsif match = scan(/#{RE::HexColor}/o)
//      encoder.text_token match, :color

//    elsif match = scan(/! *important/)
//      encoder.text_token match, :important

//    elsif match = scan(/(?:rgb|hsl)a?\([^()\n]*\)?/)
//      encoder.text_token match, :color

//    elsif match = scan(RE::AtKeyword)
//      encoder.text_token match, :directive

//    elsif match = scan(/ [+>~:;,.=()\/] /x)
//      if match == ':'
//        value_expected = true
//      elsif match == ';'
//        value_expected = false
//      end
//      encoder.text_token match, :operator

//    else
//      encoder.text_token getch, :error

//    end

//  end

//  if options[:keep_state]
//    @state = states
//    @value_expected = value_expected
//  end

//  encoder
//end

//end

//end
//end




// !important

// keywords='
//  ascent azimuth background-attachment background-color background-image background-position background-repeat background baseline bbox
//  border-collapse border-color border-spacing border-style border-top border-right border-bottom border-left border-top-color border-right-color
//  border-bottom-color border-left-color border-top-style border-right-style border-bottom-style border-left-style border-top-width border-right-width
//  border-bottom-width border-left-width border-width border cap-height caption-side centerline clear clip color content counter-increment counter-reset
//  cue-after cue-before cue cursor definition-src descent direction display elevation empty-cells float font-size-adjust font-family font-size font-stretch
//  font-style font-variant font-weight font height letter-spacing line-height list-style-image list-style-position list-style-type list-style margin-top
//  margin-right margin-bottom margin-left margin marker-offset marks mathline max-height max-width min-height min-width orphans outline-color outline-style
//  outline-width outline overflow padding-top padding-right padding-bottom padding-left padding page page-break-after page-break-before page-break-inside pause
//  pause-after pause-before pitch pitch-range play-during position quotes richness size slope src speak-header speak-numeral speak-punctuation speak speech-rate
//  stemh stemv stress table-layout text-align text-decoration text-indent text-shadow text-transform unicode-bidi unicode-range units-per-em vertical-align
//  visibility voice-family volume white-space widows width widths word-spacing x-height z-index

// values=
//  above absolute all always aqua armenian attr aural auto avoid baseline behind below bidi-override black blink block blue bold bolder both bottom braille capitalize
//  caption center center-left center-right circle close-quote code collapse compact condensed continuous counter counters crop cross crosshair cursive dashed decimal
//  decimal-leading-zero default digits disc dotted double embed embossed e-resize expanded extra-condensed extra-expanded fantasy far-left far-right fast faster fixed
//  format fuchsia gray green groove handheld hebrew help hidden hide high higher icon inline-table inline inset inside invert italic justify landscape large larger
//  left-side left leftwards level lighter lime line-through list-item local loud lower-alpha lowercase lower-greek lower-latin lower-roman lower low ltr marker maroon
//  medium message-box middle mix move narrower navy ne-resize no-close-quote none no-open-quote no-repeat normal nowrap n-resize nw-resize oblique olive once open-quote
//  outset outside overline pointer portrait pre print projection purple red relative repeat repeat-x repeat-y rgb ridge right right-side rightwards rtl run-in screen
//  scroll semi-condensed semi-expanded separate se-resize show silent silver slower slow small small-caps small-caption smaller soft solid speech spell-out square s-resize
//  static status-bar sub super sw-resize table-caption table-cell table-column table-column-group table-footer-group table-header-group table-row table-row-group teal
//  text-bottom text-top thick thin top transparent tty tv ultra-condensed ultra-expanded underline upper-alpha uppercase upper-latin upper-roman url visible wait white
//  wider w-resize x-fast x-high x-large x-loud x-low x-slow x-small x-soft xx-large xx-small yellow
//  '\\#[a-zA-Z0-9]{3,6}'
//  (-?\\d+)(\.\\d+)?(px|em|pt|\:|\%|)

// fonts=
//  [mM]onospace [tT]ahoma [vV]erdana [aA]rial [hH]elvetica [sS]ans-serif [sS]erif'


//{regex:new RegExp(this.GetKeywordsCSS(keywords),'gm'),css:'keyword'},{regex:new RegExp(this.GetValuesCSS(values),'g'),css:'value'},{regex:new RegExp(this.GetValuesCSS(fonts),'g'),css:'value'}]
//dp.sh.Highlighter.prototype.GetKeywordsCSS=function(str)
//{return'\\b([a-z_]|)'+str.replace(/ /g,'(?=:)\\b|\\b([a-z_\\*]|\\*|)')+'(?=:)\\b';}
//dp.sh.Highlighter.prototype.GetValuesCSS=function(str)
//{return'\\b'+str.replace(/ /g,'(?!-)(?!:)\\b|\\b()')+'\:\\b';}
//dp.sh.Brushes.CSS.prototype=new dp.sh.Highlighter();dp.sh.Brushes.CSS.Aliases=['css'];



class PresetCss : public IHighlightPreset, public SingletonPtr<PresetCss> {
public:
    PresetCss() {
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

#endif // CSS_PRESET
