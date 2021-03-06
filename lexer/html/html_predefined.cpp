#include "html_predefined.h"

#include <qdebug.h>

using namespace Html;

// https://html.spec.whatwg.org/
// https://www.w3.org/TR/2017/REC-html52-20171214/


Predefined::Predefined() {
//    <!--...--> 	Defines a comment
//    <!DOCTYPE>  	Defines the document type
//    <a>           Defines a hyperlink
//    <abbr>        Defines an abbreviation or an acronym
//    <acronym> 	Defines an acronym // ***Not supported in HTML5. Use <abbr> instead.
//    <address> 	Defines contact information for the author/owner of a document
//    <app>         Defines predecessor of the <applet> element // ***Not supported in HTML5.
//    <applet>      Defines an embedded applet // ***Not supported in HTML5. Use <embed> or <object> instead.
//    <area>        Defines an area inside an image-map
//    <article> 	Defines an article
//    <aside>       Defines content aside from the page content
//    <audio>       Defines sound content
//    <b>           Defines bold text
//    <base>        Specifies the base URL/target for all relative URLs in a document
//    <basefont> 	Specifies a default color, size, and font for all text in a document // ***Not supported in HTML5. Use CSS instead.
//    <bdi>         Isolates a part of text that might be formatted in a different direction from other text outside it
//    <bdo>         Overrides the current text direction
//    <bgsound>     Embed background audio track in an HTML // ***Not supported in HTML5. Use <audio> instead.
//    <big>         Defines big text // ***Not supported in HTML5. Use CSS instead.
//    <blink>       Experimental feature that could be used to cause enclosed text to blink. // ***Not supported
//    <blockquote> 	Defines a section that is quoted from another source
//    <body>        Defines the document's body
//    <br>          Defines a single line break
//    <button>      Defines a clickable button
//    <canvas>      Used to draw graphics, on the fly, via scripting (usually JavaScript)
//    <caption> 	Defines a table caption
//    <center>      Defines centered text // ***Not supported in HTML5. Use CSS instead.
//    <cite>        Defines the citation or reference to another source
//    <code>        Defines a piece of computer code
//    <col>         Specifies column properties for each column within a <colgroup> element
//    <colgroup> 	Specifies a group of one or more columns in a table for formatting
//    <command>     Represents a command which the user can invoke. Commands are often used as part of a context menu or toolbar. // ***Not supported in HTML5.
//    <comment>     Experimental way of adding comments to HTML. // ***Not supported
//    <content>     Used inside of Shadow DOM as an insertion point, and wasn't meant to be used in ordinary HTML // ***Not supported
//    <data>        Links the given content with a machine-readable translation
//    <datalist> 	Specifies a list of pre-defined options for input controls
//    <dd>          Defines a description/value of a term in a description list
//    <del>         Defines text that has been deleted from a document
//    <details> 	Defines additional details that the user can view or hide
//    <dfn>         Represents the defining instance of a term
//    <dialog>      Defines a dialog box or window
//    <dir>         Defines a directory list // ***Not supported in HTML5. Use <ul> instead.
//    <div>         Defines a section in a document
//    <dl>          Defines a description list
//    <dt>          Defines a term/name in a description list
//    <element>     Was intended to be used to define new custom DOM elements // ***Not supported
//    <em>          Defines emphasized text
//    <embed>       Defines a container for an external (non-HTML) application
//    <fieldset> 	Specifies a set of related form fields
//    <figcaption>  Defines a caption for a <figure> element
//    <figure>      Specifies self-contained content
//    <font>        Defines font, color, and size for text // ***Not supported in HTML5. Use CSS instead.
//    <footer>      Defines a footer for a document or section
//    <form>        Defines an HTML form for user input
//    <frame>       Defines a window (a frame) in a frameset // ***Not supported in HTML5.
//    <frameset> 	Defines a set of frames //*Not supported in HTML5.
//    <h1>          Defines HTML headings
//    <h2>          Defines HTML headings
//    <h3>          Defines HTML headings
//    <h4>          Defines HTML headings
//    <h5>          Defines HTML headings
//    <h6>          Defines HTML headings
//    <head>        Defines information about the document
//    <header>      Defines a header for a document or section
//    <hgroup>      Defines a group of headings.
//    <hr>          Defines a thematic change in the content
//    <html>        Defines the root of an HTML document
//    <hype>        Used to create a browser-specific "Easter Egg" effect. // ***Not supported
//    <i>           Defines a part of text in an alternate voice or mood
//    <iframe>      Defines an inline frame
//    <image>       Defines an image // ***Not supported in HTML5. Use <img> instead.
//    <img>         Defines an image
//    <input>       Defines an input control
//    <ins>         Defines a text that has been inserted into a document
//    <isindex>     Defines a single line search prompt for querying the contents of the document // ***Not supported in HTML5
//    <kbd>         Defines keyboard input
//    <keygen>      Represents a control for generating a public-private key pair.
//    <label>       Defines a label for an <input> element
//    <legend>      Defines a caption for a <fieldset> element
//    <li>          Defines a list item
//    <link>        Defines the relationship between a document and an external resource (most used to link to style sheets)
//    <listing>     Intended as a way to render HTML code on a page // ***Not supported in HTML5.
//    <main>        Specifies the main content of a document
//    <marquee>     Insert a scrolling area of text. You can control what happens when the text reaches the edges of its content area using its attributes // ***Not supported in HTML5.
//    <map>         Defines a client-side image-map
//    <mark>        Defines marked/highlighted text
//    <menu>        Represents a list of commands.
//    <menuitem>    Specify actions that can be taken with a menu.
//    <meta>        Defines metadata about an HTML document
//    <meter>       Defines a scalar measurement within a known range (a gauge)
//    <multicol>    Create a newspaper-style layout for text content // ***Not supported in HTML5.
//    <nav>         Defines a section of navigation links
//    <nextid>      Served to enable the NeXT web designing tool to generate automatic NAME labels for its anchors. // ***Not supported
//    <nobr>        Identifies text that should not be allowed to break into multiple lines // ***Not supported in HTML5.
//    <noembed>     Defines an alternate content for users that do not support embed objects // ***Not supported in HTML5.
//    <noframes> 	Defines an alternate content for users that do not support frames // ***Not supported in HTML5.
//    <noscript> 	Defines an alternate content for users that do not support client-side scripts
//    <object>      Defines an embedded object
//    <ol>          Defines an ordered list
//    <optgroup> 	Defines a group of related options in a drop-down list
//    <option>      Defines an option in a drop-down list
//    <output>      Defines the result of a calculation
//    <p>           Defines a paragraph
//    <param>       Defines a parameter for an object
//    <picture> 	Defines a container for multiple image resources
//    <plaintext>   Represent HTML code as plain text // ***Not supported in HTML5. Use the <code> or <pre> instead.
//    <pre>         Defines preformatted text
//    <progress> 	Represents the progress of a task
//    <q>           Defines a short quotation
//    <rb>          Defines a ruby annotation (for East Asian typography)
//    <rp>          Defines what to show in browsers that do not support ruby annotations
//    <rt>          Defines an explanation/pronunciation of characters (for East Asian typography)
//    <rtc>         Ruby Text Container.
//    <ruby>        Defines a ruby annotation (for East Asian typography)
//    <s>           Defines text that is no longer correct
//    <samp>        Defines sample output from a computer program
//    <script>      Defines a client-side script
//    <section> 	Defines a section in a document, such as header, footer etc.
//    <select>      Defines a drop-down list
//    <shadow>      Intended to be used as a shadow DOM insertion point. // ***Not supported
//    <slot>        A placeholder inside a web component that you can fill with your own markup, which lets you create separate DOM trees and present them together
//    <small>       Defines smaller text
//    <source>      Defines multiple media resources for media elements (<video> and <audio>)
//    <sound>       Defines sound files to HTML documents // ***Not supported in HTML5. // Use <audio> instead.
//    <spacer>      Create whitespace to web pages by replicating the effect of adding a small image to web page of the same color as the background color of the web page. // ***Not supported in HTML5.
//    <span>        Defines a section in a document
//    <strike>      Defines strikethrough text // ***Not supported in HTML5. Use <del> or <s> instead.
//    <strong>      Defines important text
//    <style>       Defines style information for a document
//    <sub>         Defines subscripted text
//    <summary> 	Defines a visible heading for a <details> element
//    <sup>         Defines superscripted text
//    <svg>         Defines a container for SVG graphics
//    <table>       Defines a table
//    <tbody>       Groups the body content in a table
//    <time>        Represents a time and/or date.
//    <td>          Defines a cell in a table
//    <template> 	Defines a template (a mechanism for holding HTML that is not to be rendered immediately when a page is loaded but may be instantiated subsequently during runtime using JavaScript.)
//    <textarea> 	Defines a multiline input control (text area)
//    <tfoot>       Groups the footer content in a table
//    <th>          Defines a header cell in a table
//    <thead>       Groups the header content in a table
//    <time>        Defines a date/time
//    <title>       Defines a title for the document
//    <tr>          Defines a row in a table
//    <track>       Defines text tracks for media elements (<video> and <audio>)
//    <tt>          Defines teletype text // ***Not supported in HTML5. Use CSS instead.
//    <u>           Defines text that should be stylistically different from normal text
//    <ul>          Defines an unordered list
//    <var>         Defines a variable
//    <video>       Defines a video or movie
//    <xmp>         Used to surround HTML example text that should be rendered without interpreting any HTML elements between the opening and closing // ***Not supported in HTML5.
//    <wbr>         Defines a possible line-break

//    keys.insert(QByteArrayLiteral("#{"), lex_interpolation);
//    keys.insert(QByteArrayLiteral("{"), lex_open_curly_bracket);
//    keys.insert(QByteArrayLiteral("}"), lex_close_curly_bracket);

//    keys.insert(QByteArrayLiteral("["), lex_open_square_bracket);
//    keys.insert(QByteArrayLiteral("]"), lex_close_square_bracket);

//    keys.insert(QByteArrayLiteral("("), lex_wrap_open);
//    keys.insert(QByteArrayLiteral(")"), lex_wrap_close);

//    keys.insert(QByteArrayLiteral("->"), lex_lambda_def);

//    keys.insert(QByteArrayLiteral("."), lex_dot);
//    keys.insert(QByteArrayLiteral(","), lex_comma);

//    keys.insert(QByteArrayLiteral(";"), lex_end_line);
//    keys.insert(QByteArrayLiteral("\r"), lex_end_line);
//    keys.insert(QByteArrayLiteral("\n"), lex_end_line);
//    keys.insert(QByteArrayLiteral("\v"), lex_end_line);
//    keys.insert(QByteArrayLiteral("\t"), lex_blanks);
//    keys.insert(QByteArrayLiteral(" "), lex_blank);


//    keys.insert(QByteArrayLiteral("__ENCODING__"), lex_method); // The script encoding of the current file
//    keys.insert(QByteArrayLiteral("__LINE__"), lex_method); // The line number of this keyword in the current file
//    keys.insert(QByteArrayLiteral("__FILE__"), lex_method); // The path to the current file.
//    keys.insert(QByteArrayLiteral("__END__"), lex_end_of_code); // Denotes the end of the regular source code section of a program file. Lines below __END__ will not be executed
//    keys.insert(QByteArrayLiteral("__method__"), lex_method); // Name of current method


//    keys.insert(QByteArrayLiteral("=begin"), lex_commentary_start); // Start of multiline comment
//    keys.insert(QByteArrayLiteral("=end"), lex_commentary_end); // End of multiline comment

//    keys.insert(QByteArrayLiteral("BEGIN"), lex_global_pre_hook); // Runs before any other code in the current file
//    keys.insert(QByteArrayLiteral("END"), lex_global_post_hook); // Runs after any other code in the current file

//    keys.insert(QByteArrayLiteral("alias"), lex_alias); // Creates an alias between two methods (and other things)
//    keys.insert(QByteArrayLiteral("and"), lex_operator_and_word); // Short-circuit Boolean and with lower precedence than &&

//    keys.insert(QByteArrayLiteral("begin"), lex_begin); // Starts an exception handling block
//    keys.insert(QByteArrayLiteral("break"), lex_loop_break); // Leaves a block early
//    keys.insert(QByteArrayLiteral("case"), lex_case); // Starts a case expression
//    keys.insert(QByteArrayLiteral("class"), lex_class_def); // Creates or opens a class
//    keys.insert(QByteArrayLiteral("def"), lex_method_def); // Defines a method
//    keys.insert(QByteArrayLiteral("defined?"), lex_method); // Returns a string describing its argument
//    keys.insert(QByteArrayLiteral("do"), lex_do); // Starts a block
//    keys.insert(QByteArrayLiteral("else"), lex_else); // The unhandled condition in case, if and unless expressions
//    keys.insert(QByteArrayLiteral("elsif"), lex_elsif); // An alternate condition for an if expression
//    keys.insert(QByteArrayLiteral("end"), lex_end); // The end of a syntax block. Used by classes, modules, methods, exception handling and control expressions
//    keys.insert(QByteArrayLiteral("ensure"), lex_block_ensure); // Starts a section of code that is always run when an exception is raised

//    keys.insert(QByteArrayLiteral("eql?"), lex_operator_comparison); // receiver and argument have both the same type and equal values
//    keys.insert(QByteArrayLiteral("equal?"), lex_operator_equality); // receiver and argument have the same object id

//    keys.insert(QByteArrayLiteral("extend"), lex_extend);
//    keys.insert(QByteArrayLiteral("false"), lex_method); // Boolean false
//    keys.insert(QByteArrayLiteral("for"), lex_for); // A loop that is similar to using the each method
//    keys.insert(QByteArrayLiteral("if"), lex_if); // Used for if and modifier if expressions
//    keys.insert(QByteArrayLiteral("in"), lex_in); // Used to separate the iterable object and iterator variable in a for loop
//    keys.insert(QByteArrayLiteral("include"), lex_include);

//    keys.insert(QByteArrayLiteral("lambda"), lex_lambda_def);
//    keys.insert(QByteArrayLiteral("module"), lex_module_def); // Creates or opens a module
//    keys.insert(QByteArrayLiteral("next"), lex_loop_next); // Skips the rest of the block
//    keys.insert(QByteArrayLiteral("new"), lex_method);
//    keys.insert(QByteArrayLiteral("nil"), lex_method); // A false value usually indicating “no value” or “unknown”
//    keys.insert(QByteArrayLiteral("not"), lex_operator_not); // Inverts the following boolean expression
//    keys.insert(QByteArrayLiteral("or"), lex_operator_or_word); // Boolean or with lower precedence than ||
//    keys.insert(QByteArrayLiteral("private"), lex_visibility_scope);
//    keys.insert(QByteArrayLiteral("proc"), lex_proc_def);
//    keys.insert(QByteArrayLiteral("protected"), lex_visibility_scope);
//    keys.insert(QByteArrayLiteral("public"), lex_visibility_scope);
//    keys.insert(QByteArrayLiteral("raise"), lex_raise);
//    keys.insert(QByteArrayLiteral("redo"), lex_loop_redo); // Restarts execution in the current block
//    keys.insert(QByteArrayLiteral("require"), lex_require);
//    keys.insert(QByteArrayLiteral("rescue"), lex_block_rescue); // Starts an exception section of code in a begin block
//    keys.insert(QByteArrayLiteral("retry"), lex_block_retry); // Retries an exception block
//    keys.insert(QByteArrayLiteral("return"), lex_return); // Exits a method
//    keys.insert(QByteArrayLiteral("self"), lex_self); // The object the current method is attached to
//    keys.insert(QByteArrayLiteral("super"), lex_super); // Calls the current method in a superclass
//    keys.insert(QByteArrayLiteral("then"), lex_then); // Indicates the end of conditional blocks in control structures
//    keys.insert(QByteArrayLiteral("true"), lex_method); // Boolean true
//    keys.insert(QByteArrayLiteral("undef"), lex_undef); // Prevents a class or module from responding to a method call
//    keys.insert(QByteArrayLiteral("unless"), lex_unless); // Used for unless and modifier unless expressions
//    keys.insert(QByteArrayLiteral("until"), lex_until); // Creates a loop that executes until the condition is true
//    keys.insert(QByteArrayLiteral("when"), lex_when); // A condition in a case expression
//    keys.insert(QByteArrayLiteral("while"), lex_while); // Creates a loop that executes while the condition is true
//    keys.insert(QByteArrayLiteral("yield"), lex_yield); // Starts execution of the block sent to the current method
//    keys.insert(QByteArrayLiteral("loop"), lex_loop); // Starts infinite loop



//    keys.insert(QByteArrayLiteral("+"), lex_operator_add);
//    keys.insert(QByteArrayLiteral("-"), lex_operator_minus);
//    keys.insert(QByteArrayLiteral("*"), lex_operator_multiplication);
//    keys.insert(QByteArrayLiteral("/"), lex_operator_division);
//    keys.insert(QByteArrayLiteral("%"), lex_operator_modulus);
//    keys.insert(QByteArrayLiteral("**"), lex_operator_exponentiation);

//    keys.insert(QByteArrayLiteral("+="), lex_operator_add_assigment);
//    keys.insert(QByteArrayLiteral("-="), lex_operator_minus_assigment);
//    keys.insert(QByteArrayLiteral("*="), lex_operator_multiplication_assigment);
//    keys.insert(QByteArrayLiteral("/="), lex_operator_division_assigment);
//    keys.insert(QByteArrayLiteral("%="), lex_operator_modulus_assigment);
//    keys.insert(QByteArrayLiteral("**="), lex_operator_exponentiation_assigment);

//    keys.insert(QByteArrayLiteral("="), lex_operator_assigment);
//    keys.insert(QByteArrayLiteral("=="), lex_operator_comparison);
//    keys.insert(QByteArrayLiteral("!="), lex_operator_not_equal);
//    keys.insert(QByteArrayLiteral(">"), lex_operator_great);
//    keys.insert(QByteArrayLiteral("<"), lex_operator_less);
//    keys.insert(QByteArrayLiteral(">="), lex_operator_great_eql);
//    keys.insert(QByteArrayLiteral("<="), lex_operator_less_eql);
//    keys.insert(QByteArrayLiteral("<=>"), lex_operator_sort);
//    keys.insert(QByteArrayLiteral("==="), lex_operator_equality);
//    keys.insert(QByteArrayLiteral(".."), lex_dot_dot);
//    keys.insert(QByteArrayLiteral("..."), lex_dot_dot_dot);

//    keys.insert(QByteArrayLiteral("&"), lex_operator_bit_and);
//    keys.insert(QByteArrayLiteral("|"), lex_operator_bit_or);
//    keys.insert(QByteArrayLiteral("^"), lex_operator_bit_exclusive_or);
//    keys.insert(QByteArrayLiteral("~"), lex_operator_bit_not);
//    keys.insert(QByteArrayLiteral("<<"), lex_operator_bit_left_shift);
//    keys.insert(QByteArrayLiteral(">>"), lex_operator_bit_right_shift);

//    keys.insert(QByteArrayLiteral("&="), lex_operator_bit_and_assigment);
//    keys.insert(QByteArrayLiteral("|="), lex_operator_bit_or_assigment);
//    keys.insert(QByteArrayLiteral("^="), lex_operator_bit_exclusive_or_assigment);
//    keys.insert(QByteArrayLiteral("<<="), lex_operator_bit_left_shift_assigment);
//    keys.insert(QByteArrayLiteral(">>="), lex_operator_bit_right_shift_assigment);


//    keys.insert(QByteArrayLiteral("=>"), lex_rocket);
//    keys.insert(QByteArrayLiteral("?"), lex_question_mark);
//    keys.insert(QByteArrayLiteral(":"), lex_colon);

//    keys.insert(QByteArrayLiteral("!"), lex_operator_not);
//    keys.insert(QByteArrayLiteral("&&"), lex_operator_and);
//    keys.insert(QByteArrayLiteral("||"), lex_operator_or);


//    keys.insert(QByteArrayLiteral("&&="), lex_operator_and_assigment);
//    keys.insert(QByteArrayLiteral("||="), lex_operator_or_assigment);

//    keys.insert(QByteArrayLiteral("::"), lex_resolution);


//    keys.insert(QByteArrayLiteral("TRUE"), lex_method); // Synonym for true
//    keys.insert(QByteArrayLiteral("FALSE"), lex_method); // Synonym for false
//    keys.insert(QByteArrayLiteral("NIL"), lex_method); // Synonym for nil
//    keys.insert(QByteArrayLiteral("ARGF"), lex_method); // An object providing access to virtual concatenation of files passed as command-line arguments or standard input if there are no command-line arguments. A synonym for $<
//    keys.insert(QByteArrayLiteral("ARGV"), lex_method); // An array containing the command-line arguments passed to the program. A synonym for $*
//    keys.insert(QByteArrayLiteral("DATA"), lex_method); // An input stream for reading the lines of code following the __END__ directive. Not defined if __END__ isn't present in code.
//    keys.insert(QByteArrayLiteral("ENV"), lex_method); // A hash-like object containing the program's environment variables. ENV can be handled as a hash
//    keys.insert(QByteArrayLiteral("RUBY_PLATFORM"), lex_method); // A string indicating the platform of the Ruby interpreter.
//    keys.insert(QByteArrayLiteral("RUBY_RELEASE_DATE"), lex_method); // A string indicating the release date of the Ruby interpreter
//    keys.insert(QByteArrayLiteral("RUBY_VERSION"), lex_method); // A string indicating the version of the Ruby interpreter
//    keys.insert(QByteArrayLiteral("STDERR"), lex_method); // Standard error output stream. Default value of $stderr
//    keys.insert(QByteArrayLiteral("STDIN"), lex_method); // Standard input stream. Default value of $stdin
//    keys.insert(QByteArrayLiteral("STDOUT"), lex_method); // Standard output stream. Default value of $stdout
//    keys.insert(QByteArrayLiteral("TOPLEVEL_BINDING"), lex_method); // A binding object at Ruby's top level.

//    keys.insert(QByteArrayLiteral("$!"), lex_method); // The last exception object raised. The exception object can also be accessed using => in rescue clause.
//    keys.insert(QByteArrayLiteral("$@"), lex_method); // The stack backtrace for the last exception raised. The stack backtrace information can retrieved by Exception#backtrace method of the last exception.
//    keys.insert(QByteArrayLiteral("$/"), lex_method); // The input record separator (newline by default). gets, readline, etc., take their input record separator as optional argument.
//    keys.insert(QByteArrayLiteral("$\\"), lex_method); // The output record separator (nil by default).
//    keys.insert(QByteArrayLiteral("$,"), lex_method); // The output separator between the arguments to print and Array#join (nil by default). You can specify separator explicitly to Array#join.
//    keys.insert(QByteArrayLiteral("$;"), lex_method); // The default separator for split (nil by default). You can specify separator explicitly for String#split.
//    keys.insert(QByteArrayLiteral("$."), lex_method); // The number of the last line read from the current input file. Equivalent to ARGF.lineno.
//    keys.insert(QByteArrayLiteral("$<"), lex_method); // Synonym for ARGF.
//    keys.insert(QByteArrayLiteral("$>"), lex_method); // Synonym for $defout.
//    keys.insert(QByteArrayLiteral("$0"), lex_method); // The name of the current Ruby program being executed.

//    keys.insert(QByteArrayLiteral("$$"), lex_method); // The process pid of the current Ruby program being executed.
//    keys.insert(QByteArrayLiteral("$?"), lex_method); // The exit status of the last process terminated.
//    keys.insert(QByteArrayLiteral("$:"), lex_method); // Synonym for $LOAD_PATH.
//    keys.insert(QByteArrayLiteral("$DEBUG"), lex_method); // True if the -d or --debug command-line option is specified.
//    keys.insert(QByteArrayLiteral("$defout"), lex_method); // The destination output for print and printf ($stdout by default).
//    keys.insert(QByteArrayLiteral("$F"), lex_method); // The variable that receives the output from split when -a is specified. This variable is set if the -a command-line option is specified along with the -p or -n option.
//    keys.insert(QByteArrayLiteral("$FILENAME"), lex_method); // The name of the file currently being read from ARGF. Equivalent to ARGF.filename.
//    keys.insert(QByteArrayLiteral("$LOAD_PATH"), lex_method); // An array holding the directories to be searched when loading files with the load and require methods.
//    keys.insert(QByteArrayLiteral("$SAFE"), lex_method); // The security level
//    //    0 → No checks are performed on externally supplied (tainted) data. (default)
//    //    1 → Potentially dangerous operations using tainted data are forbidden.
//    //    2 → Potentially dangerous operations on processes and files are forbidden.
//    //    3 → All newly created objects are considered tainted.
//    //    4 → Modification of global data is forbidden.

//    keys.insert(QByteArrayLiteral("$stdin"), lex_method); // Standard input (STDIN by default).
//    keys.insert(QByteArrayLiteral("$stdout"), lex_method); // Standard output (STDOUT by default).
//    keys.insert(QByteArrayLiteral("$stderr"), lex_method); // Standard error (STDERR by default).
//    keys.insert(QByteArrayLiteral("$VERBOSE"), lex_method); // True if the -v, -w, or --verbose command-line option is specified.

//    // $- x // The value of interpreter option -x (x=0, a, d, F, i, K, l, p, v). These options are listed below
//    keys.insert(QByteArrayLiteral("$-0"), lex_method); // The value of interpreter option -x and alias of $/.
//    keys.insert(QByteArrayLiteral("$-a"), lex_method); // The value of interpreter option -x and true if option -a is set. Read-only.
//    keys.insert(QByteArrayLiteral("$-d"), lex_method); // The value of interpreter option -x and alias of $DEBUG
//    keys.insert(QByteArrayLiteral("$-F"), lex_method); // The value of interpreter option -x and alias of $;.
//    keys.insert(QByteArrayLiteral("$-i"), lex_method); // The value of interpreter option -x and in in-place-edit mode, holds the extension, otherwise nil. Can enable or disable in-place-edit mode.
//    keys.insert(QByteArrayLiteral("$-K"), lex_method); // The value of interpreter option -x and alias of $:.
//    keys.insert(QByteArrayLiteral("$-l"), lex_method); // The value of interpreter option -x and true if option -lis set. Read-only.
//    keys.insert(QByteArrayLiteral("$-p"), lex_method); // The value of interpreter option -x and true if option -pis set. Read-only.
//    keys.insert(QByteArrayLiteral("$-v"), lex_method); //

//    keys.insert(QByteArrayLiteral("$_"), lex_method); // The local variable, last string read by gets or readline in the current scope.
//    keys.insert(QByteArrayLiteral("$~"), lex_method); // The local variable, MatchData relating to the last match. Regex#match method returns the last match information.

////    // $ n ($1, $2, $3...) // The string matched in the nth group of the last pattern match. Equivalent to m[n], where m is a MatchData object.
////    for(int i = 1; i < 254; i++)
////        keys.insert('$' + QByteArray::number(i), lex_method);

//    keys.insert(QByteArrayLiteral("$&"), lex_method); // The string matched in the last pattern match. Equivalent to m[0], where m is a MatchData object.
//    keys.insert(QByteArrayLiteral("$`"), lex_method); // The string preceding the match in the last pattern match. Equivalent to m.pre_match, where m is a MatchData object.
//    keys.insert(QByteArrayLiteral("$'"), lex_method); // The string following the match in the last pattern match. Equivalent to m.post_match, where m is a MatchData object.
//    keys.insert(QByteArrayLiteral("$+"), lex_method); // The string corresponding to the last successfully matched group in the last pattern match.


//    //        keys.insert(QByteArrayLiteral("attr"), true);
//    //        keys.insert(QByteArrayLiteral("attr_accessor"), true);
//    //        keys.insert(QByteArrayLiteral("attr_reader"), true);
//    //        keys.insert(QByteArrayLiteral("attr_writer"), true);
}


bool Predefined::hasKey(const QByteArray & key) { return keys.contains(key); }
StateLexem Predefined::lexem(const QByteArray & key) {
    return keys.value(key, lex_word);
}
