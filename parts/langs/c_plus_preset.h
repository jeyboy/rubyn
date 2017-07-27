#ifndef C_PLUS_PRESET
#define C_PLUS_PRESET

#include "parts/highligters/ihighlight_preset.h"


//KEYWORDS = [
//  'and', 'and_eq', 'asm', 'bitand', 'bitor', 'break',
//  'case', 'catch', 'class', 'compl', 'const_cast',
//  'continue', 'default', 'delete', 'do', 'dynamic_cast', 'else',
//  'enum', 'export', 'for', 'goto', 'if', 'namespace', 'new',
//  'not', 'not_eq', 'or', 'or_eq', 'reinterpret_cast', 'return',
//  'sizeof', 'static_cast', 'struct', 'switch', 'template',
//  'throw', 'try', 'typedef', 'typeid', 'typename', 'union',
//  'while', 'xor', 'xor_eq',
//]  # :nodoc:

//PREDEFINED_TYPES = [
//  'bool', 'char', 'double', 'float', 'int', 'long',
//  'short', 'signed', 'unsigned', 'wchar_t', 'string',
//]  # :nodoc:
//PREDEFINED_CONSTANTS = [
//  'false', 'true',
//  'EOF', 'NULL',
//]  # :nodoc:
//PREDEFINED_VARIABLES = [
//  'this',
//]  # :nodoc:
//DIRECTIVES = [
//  'auto', 'const', 'explicit', 'extern', 'friend', 'inline', 'mutable', 'operator',
//  'private', 'protected', 'public', 'register', 'static', 'using', 'virtual', 'void',
//  'volatile',
//]

//def scan_tokens encoder, options

//  state = :initial
//  label_expected = true
//  case_expected = false
//  label_expected_before_preproc_line = nil
//  in_preproc_line = false

//  until eos?

//    case state

//    when :initial

//      if match = scan(/ \s+ | \\\n /x)
//        if in_preproc_line && match != "\\\n" && match.index(?\n)
//          in_preproc_line = false
//          label_expected = label_expected_before_preproc_line
//        end
//        encoder.text_token match, :space

//      elsif match = scan(%r! // [^\n\\]* (?: \\. [^\n\\]* )* | /\* (?: .*? \*/ | .* ) !mx)
//        encoder.text_token match, :comment

//      elsif match = scan(/ \# \s* if \s* 0 /x)
//        match << scan_until(/ ^\# (?:elif|else|endif) .*? $ | \z /xm) unless eos?
//        encoder.text_token match, :comment

//      elsif match = scan(/ [-+*=<>?:;,!&^|()\[\]{}~%]+ | \/=? | \.(?!\d) /x)
//        label_expected = match =~ /[;\{\}]/
//        if case_expected
//          label_expected = true if match == ':'
//          case_expected = false
//        end
//        encoder.text_token match, :operator

//      elsif match = scan(/ [A-Za-z_][A-Za-z_0-9]* /x)
//        kind = IDENT_KIND[match]
//        if kind == :ident && label_expected && !in_preproc_line && scan(/:(?!:)/)
//          kind = :label
//          match << matched
//        else
//          label_expected = false
//          if kind == :keyword
//            case match
//            when 'class'
//              state = :class_name_expected
//            when 'case', 'default'
//              case_expected = true
//            end
//          end
//        end
//        encoder.text_token match, kind

//      elsif match = scan(/\$/)
//        encoder.text_token match, :ident

//      elsif match = scan(/L?"/)
//        encoder.begin_group :string
//        if match[0] == ?L
//          encoder.text_token match, 'L', :modifier
//          match = '"'
//        end
//        state = :string
//        encoder.text_token match, :delimiter

//      elsif match = scan(/#[ \t]*(\w*)/)
//        encoder.text_token match, :preprocessor
//        in_preproc_line = true
//        label_expected_before_preproc_line = label_expected
//        state = :include_expected if self[1] == 'include'

//      elsif match = scan(/ L?' (?: [^\'\n\\] | \\ #{ESCAPE} )? '? /ox)
//        label_expected = false
//        encoder.text_token match, :char

//      elsif match = scan(/0[xX][0-9A-Fa-f]+/)
//        label_expected = false
//        encoder.text_token match, :hex

//      elsif match = scan(/(?:0[0-7]+)(?![89.eEfF])/)
//        label_expected = false
//        encoder.text_token match, :octal

//      elsif match = scan(/(?:\d+)(?![.eEfF])L?L?/)
//        label_expected = false
//        encoder.text_token match, :integer

//      elsif match = scan(/\d[fF]?|\d*\.\d+(?:[eE][+-]?\d+)?[fF]?|\d+[eE][+-]?\d+[fF]?/)
//        label_expected = false
//        encoder.text_token match, :float

//      else
//        encoder.text_token getch, :error

//      end

//    when :string
//      if match = scan(/[^\\"]+/)
//        encoder.text_token match, :content
//      elsif match = scan(/"/)
//        encoder.text_token match, :delimiter
//        encoder.end_group :string
//        state = :initial
//        label_expected = false
//      elsif match = scan(/ \\ (?: #{ESCAPE} | #{UNICODE_ESCAPE} ) /mox)
//        encoder.text_token match, :char
//      elsif match = scan(/ \\ | $ /x)
//        encoder.end_group :string
//        encoder.text_token match, :error unless match.empty?
//        state = :initial
//        label_expected = false
//      else
//        raise_inspect "else case \" reached; %p not handled." % peek(1), encoder
//      end

//    when :include_expected
//      if match = scan(/<[^>\n]+>?|"[^"\n\\]*(?:\\.[^"\n\\]*)*"?/)
//        encoder.text_token match, :include
//        state = :initial

//      elsif match = scan(/\s+/)
//        encoder.text_token match, :space
//        state = :initial if match.index ?\n

//      else
//        state = :initial

//      end

//    when :class_name_expected
//      if match = scan(/ [A-Za-z_][A-Za-z_0-9]* /x)
//        encoder.text_token match, :class
//        state = :initial

//      elsif match = scan(/\s+/)
//        encoder.text_token match, :space

//      else
//        encoder.text_token getch, :error
//        state = :initial

//      end

//    else
//      raise_inspect 'Unknown state', encoder

//    end

//  end

//  if state == :string
//    encoder.end_group :string
//  end

//  encoder
//end

//end

//end
//end


//datatypes=
//'ATOM BOOL BOOLEAN BYTE CHAR COLORREF DWORD DWORDLONG DWORD_PTR DWORD32 DWORD64 FLOAT HACCEL HALF_PTR HANDLE HBITMAP HBRUSH HCOLORSPACE HCONV
//  HCONVLIST HCURSOR HDC HDDEDATA HDESK HDROP HDWP HENHMETAFILE HFILE HFONT HGDIOBJ HGLOBAL HHOOK HICON HINSTANCE HKEY HKL HLOCAL HMENU HMETAFILE
//  HMODULE HMONITOR HPALETTE HPEN HRESULT HRGN HRSRC HSZ HWINSTA HWND INT INT_PTR INT32 INT64 LANGID LCID LCTYPE LGRPID LONG LONGLONG LONG_PTR LONG32
//  LONG64 LPARAM LPBOOL LPBYTE LPCOLORREF LPCSTR LPCTSTR LPCVOID LPCWSTR LPDWORD LPHANDLE LPINT LPLONG LPSTR LPTSTR LPVOID LPWORD LPWSTR LRESULT PBOOL
//  PBOOLEAN PBYTE PCHAR PCSTR PCTSTR PCWSTR PDWORDLONG PDWORD_PTR PDWORD32 PDWORD64 PFLOAT PHALF_PTR PHANDLE PHKEY PINT PINT_PTR PINT32 PINT64 PLCID
//  PLONG PLONGLONG PLONG_PTR PLONG32 PLONG64 POINTER_32 POINTER_64 PSHORT PSIZE_T PSSIZE_T PSTR PTBYTE PTCHAR PTSTR PUCHAR PUHALF_PTR PUINT PUINT_PTR
//  PUINT32 PUINT64 PULONG PULONGLONG PULONG_PTR PULONG32 PULONG64 PUSHORT PVOID PWCHAR PWORD PWSTR SC_HANDLE SC_LOCK SERVICE_STATUS_HANDLE SHORT SIZE_T
//  SSIZE_T TBYTE TCHAR UCHAR UHALF_PTR UINT UINT_PTR UINT32 UINT64 ULONG ULONGLONG ULONG_PTR ULONG32 ULONG64 USHORT USN VOID WCHAR WORD WPARAM WPARAM
//  WPARAM char bool short int __int32 __int64 __int8 __int16 long float double __wchar_t clock_t _complex _dev_t _diskfree_t div_t ldiv_t _exception
//  _EXCEPTION_POINTERS FILE _finddata_t _finddatai64_t _wfinddata_t _wfinddatai64_t __finddata64_t '+'__wfinddata64_t _FPIEEE_RECORD fpos_t _HEAPINFO
//  _HFILE lconv intptr_t jmp_buf mbstate_t _off_t _onexit_t _PNH ptrdiff_t _purecall_handler sig_atomic_t size_t _stat __stat64 _stati64 terminate_function
//  time_t __time64_t _timeb __timeb64 tm uintptr_t _utimbuf va_list wchar_t wctrans_t wctype_t wint_t signed
//keywords=
//  break case catch class const __finally __exception __try const_cast continue private public protected __declspec default delete deprecated dllexport
//  dllimport do dynamic_cast else enum explicit extern if for friend goto inline mutable naked namespace new noinline noreturn nothrow register
//  reinterpret_cast return selectany sizeof static static_cast struct switch template this thread throw true false try typedef typeid typename union
//  using uuid virtual void volatile whcar_t while


class CPlusPreset : public IHighlightPreset, public SingletonPtr<CPlusPreset> {
public:
    CPlusPreset() {
        HighlightingRule rule;

        QString keywords = "void class char volatile template typedef union unsigned virtual typename const double enum explicit friend private protected public inline short signals static struct slots signed int long namespace operator";
        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("^ *#.*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_preprocessing);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
        highlighting_rules.append(rule);


        highlighting_rules.append(singleQuotationRule());


        highlighting_rules.append(doubleQuotationRule());


        highlighting_rules.append(numbersRule());


        rule.pattern = QRegularExpression("//[^\n]*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
        highlighting_rules.append(rule);

        comment_start_expression = QRegularExpression("/\\*");
        comment_end_expression = QRegularExpression("\\*/");
    }
};

#endif // C_PLUS_PRESET
