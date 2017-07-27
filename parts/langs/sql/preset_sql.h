#ifndef SQL_PRESET
#define SQL_PRESET

#include "parts/highligters/ihighlight_preset.h"

//KEYWORDS = %w(
//  all and any as before begin between by case check collate
//  each else end exists
//  for foreign from full group having if in inner is join
//  like not of on or order outer over references
//  then to union using values when where
//  left right distinct
//)

//OBJECTS = %w(
//  database databases table tables column columns fields index constraint
//  constraints transaction function procedure row key view trigger
//)

//COMMANDS = %w(
//  add alter comment create delete drop grant insert into select update set
//  show prompt begin commit rollback replace truncate
//)

//PREDEFINED_TYPES = %w(
//  char varchar varchar2 enum binary text tinytext mediumtext
//  longtext blob tinyblob mediumblob longblob timestamp
//  date time datetime year double decimal float int
//  integer tinyint mediumint bigint smallint unsigned bit
//  bool boolean hex bin oct
//)

//PREDEFINED_FUNCTIONS = %w( sum cast substring abs pi count min max avg now )

//DIRECTIVES = %w(
//  auto_increment unique default charset initially deferred
//  deferrable cascade immediate read write asc desc after
//  primary foreign return engine
//)

//PREDEFINED_CONSTANTS = %w( null true false )

//IDENT_KIND = WordList::CaseIgnoring.new(:ident).
//  add(KEYWORDS, :keyword).
//  add(OBJECTS, :type).
//  add(COMMANDS, :class).
//  add(PREDEFINED_TYPES, :predefined_type).
//  add(PREDEFINED_CONSTANTS, :predefined_constant).
//  add(PREDEFINED_FUNCTIONS, :predefined).
//  add(DIRECTIVES, :directive)

//ESCAPE = / [rbfntv\n\\\/'"] | x[a-fA-F0-9]{1,2} | [0-7]{1,3} | . /mx
//UNICODE_ESCAPE =  / u[a-fA-F0-9]{4} | U[a-fA-F0-9]{8} /x

//STRING_PREFIXES = /[xnb]|_\w+/i

//STRING_CONTENT_PATTERN = {
//  '"' => / (?: [^\\"] | "" )+ /x,
//  "'" => / (?: [^\\'] | '' )+ /x,
//  '`' => / (?: [^\\`] | `` )+ /x,
//}

//def scan_tokens encoder, options

//  state = :initial
//  string_type = nil
//  string_content = ''
//  name_expected = false

//  until eos?

//    if state == :initial

//      if match = scan(/ \s+ | \\\n /x)
//        encoder.text_token match, :space

//      elsif match = scan(/(?:--\s?|#).*/)
//        encoder.text_token match, :comment

//      elsif match = scan(%r( /\* (!)? (?: .*? \*/ | .* ) )mx)
//        encoder.text_token match, self[1] ? :directive : :comment

//      elsif match = scan(/ [*\/=<>:;,!&^|()\[\]{}~%] | [-+\.](?!\d) /x)
//        name_expected = true if match == '.' && check(/[A-Za-z_]/)
//        encoder.text_token match, :operator

//      elsif match = scan(/(#{STRING_PREFIXES})?([`"'])/o)
//        prefix = self[1]
//        string_type = self[2]
//        encoder.begin_group :string
//        encoder.text_token prefix, :modifier if prefix
//        match = string_type
//        state = :string
//        encoder.text_token match, :delimiter

//      elsif match = scan(/ @? [A-Za-z_][A-Za-z_0-9]* /x)
//        encoder.text_token match, name_expected ? :ident : (match[0] == ?@ ? :variable : IDENT_KIND[match])
//        name_expected = false

//      elsif match = scan(/0[xX][0-9A-Fa-f]+/)
//        encoder.text_token match, :hex

//      elsif match = scan(/0[0-7]+(?![89.eEfF])/)
//        encoder.text_token match, :octal

//      elsif match = scan(/[-+]?(?>\d+)(?![.eEfF])/)
//        encoder.text_token match, :integer

//      elsif match = scan(/[-+]?(?:\d[fF]|\d*\.\d+(?:[eE][+-]?\d+)?|\d+[eE][+-]?\d+)/)
//        encoder.text_token match, :float

//      elsif match = scan(/\\N/)
//        encoder.text_token match, :predefined_constant

//      else
//        encoder.text_token getch, :error

//      end

//    elsif state == :string
//      if match = scan(STRING_CONTENT_PATTERN[string_type])
//        encoder.text_token match, :content
//      elsif match = scan(/["'`]/)
//        if string_type == match
//          if peek(1) == string_type  # doubling means escape
//            encoder.text_token match + getch, :content
//          else
//            encoder.text_token match, :delimiter
//            encoder.end_group :string
//            state = :initial
//            string_type = nil
//          end
//        else
//          encoder.text_token match, :content
//        end
//      elsif match = scan(/ \\ (?: #{ESCAPE} | #{UNICODE_ESCAPE} ) /mox)
//        encoder.text_token match, :char
//      elsif match = scan(/ \\ . /mox)
//        encoder.text_token match, :content
//      elsif match = scan(/ \\ | $ /x)
//        encoder.text_token match, :error unless match.empty?
//        encoder.end_group :string
//        state = :initial
//      else
//        raise "else case \" reached; %p not handled." % peek(1), encoder
//      end

//    else
//      raise 'else-case reached', encoder

//    end

//  end

//  if state == :string
//    encoder.end_group state
//  end

//  encoder

//end

//end

//end
//end


class PresetSQL : public IHighlightPreset, public SingletonPtr<PresetSQL> {
public:
    PresetSQL() {
        HighlightingRule rule;

        QString keywords = "begin commit rollback select from where explain insert into values update create delete drop grant revoke lock set truncate as join on table view order group by having";
        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b", QRegularExpression::CaseInsensitiveOption);
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
        highlighting_rules.append(rule);


        keywords = "anydata anydataset anytype array bfile bigint binary_double binary_float binary_integer bit blob boolean cfile char character clob date datetime day dburitype dec decimal double enum float float4 float8 flob httpuritype int int16 int2 int24 int4 int8 integer interval lob long longblob longlong longtext mediumblob mediumtext mlslabel month national nchar nclob newdate null number numeric nvarchar object pls_integer precision raw real record rowid second short single smallint time timestamp tiny tinyblob tinyint tinytext urifactorytype uritype urowid utc_date utc_time utc_timestamp varchar varchar2 varray varying xmltype year zone";
        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b", QRegularExpression::CaseInsensitiveOption);
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
        highlighting_rules.append(rule);


        keywords = "abort abs absolute access action ada add admin after aggregate alias all allocate alter analyse analyze and any are asc asensitive assertion assignment asymmetric at atomic audit authorization avg backward before between bigint binary bit_length bitvar both breadth c cache call called cardinality cascade cascaded case cast catalog catalog_name chain change char_length character_length character_set_catalog character_set_name character_set_schema characteristics check checked checkpoint class class_origin close cluster coalesce cobol collate collation collation_catalog collation_name collation_schema column column_name command_function command_function_code comment committed completion compress condition condition_number connect connection connection_name constraint constraint_catalog constraint_name constraint_schema constraints constructor contains continue conversion convert copy corresponding count createdb createuser cross cube current current_date current_path current_role current_time current_timestamp current_user cursor cursor_name cycle data database databases datetime_interval_code datetime_interval_precision day_hour day_microsecond day_minute day_second deallocate declare default deferrable deferred defined definer delayed delimiter delimiters depth deref desc describe descriptor destroy destructor deterministic diagnostics dictionary disconnect dispatch distinct distinctrow div do domain dual dynamic dynamic_function dynamic_function_code each else elseif elsif enclosed encoding encrypted end end-exec equals escape escaped every except exception exclusive exec execute existing exists exit external extract false fetch file final first for force foreign fortran forward found free freeze full fulltext function g general generated get global go goto granted grouping handler hierarchy high_priority hold host hour hour_microsecond hour_minute hour_second identified identity if ignore ilike immediate immutable implementation implicit in increment index indicator infile infix inherits initial initialize initially inner inout input insensitive instance instantiable instead int1 int3 intersect invoker is isnull isolation iterate k key key_member key_type keys kill lancompiler language large last lateral leading leave left length less level like limit lines listen load local localtime localtimestamp location locator loop low_priority lower m map match max maxextents maxvalue mediumint message_length message_octet_length message_text method middleint min minus minute minute_microsecond minute_second minvalue mod mode modifies modify module more move mumps name names natural new next no no_write_to_binlog noaudit nocompress nocreatedb nocreateuser none not nothing notify notnull nowait nullable nullif octet_length of off offline offset oids old online only open operation operator optimize option optionally options or ordinality out outer outfile output overlaps overlay overriding owner pad parameter parameter_mode parameter_name parameter_ordinal_position parameter_specific_catalog parameter_specific_name parameter_specific_schema parameters partial pascal password path pctfree pendant placing pli position postfix prefix preorder prepare preserve primary prior privileges procedural procedure public purge raid0 read reads recheck recursive ref references referencing regexp reindex relative release rename repeat repeatable replace require reset resource restrict result return returned_length returned_octet_length returned_sqlstate returns right rlike role rollup routine routine_catalog routine_name routine_schema row row_count rowlabel rownum rows rule savepoint scale schema schema_name schemas scope scroll search second_microsecond section security self sensitive separator sequence serializable server_name session session_user setof sets share show similar simple size some soname source space spatial specific specific_name specifictype sql sqlcode sqlerror sqlexception sqlstate sqlwarning ssl stable start starting state statement static statistics stdin stdout storage straight_join strict structure style subclass_origin sublist substring successful sum symmetric synonym sysdate sysid system system_user table_name temp template temporary terminate terminated than then timezone_hour timezone_minute to toast trailing transaction transaction_active transactions_committed transactions_rolled_back transform transforms translate translation treat trigger true type uid undo union unique unlock unsigned usage use user using validate varbinary varcharacter when whenever while with write x509 xor year_month zerofillzgium";
        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b", QRegularExpression::CaseInsensitiveOption);
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("`.*?`|'.*?'");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_single_quotation);
        highlighting_rules.append(rule);


        highlighting_rules.append(numbersRule());


        highlighting_rules.append(doubleQuotationRule());


        rule.pattern = QRegularExpression("--[^\n]*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
        highlighting_rules.append(rule);

        comment_start_expression = QRegularExpression("/\\*");
        comment_end_expression = QRegularExpression("\\*/");
    }
};

#endif // SQL_PRESET
