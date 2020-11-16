#include "css_predefined.h"

#include <qdebug.h>

using namespace Css;

// https://base64.guru/converter/encode/image

// BASE64 decode
//QString base64img = jsonObj["photo"].toString();
//QByteArray by = QByteArray::fromBase64(base64img.toLatin1());
//QImage img = QImage::fromData(by,"JPEG");



//-ms-, mso-	Microsoft
//-moz-	Mozilla
//-o-, -xv-	Opera Software
//-atsc-	Advanced Television Standards Committee
//-wap-	The WAP Forum
//-khtml-	KDE
//-webkit-	Apple
//prince-	YesLogic
//-ah-	Antenna House
//-hp-	Hewlett Packard
//-ro-	Real Objects
//-rim-	Research In Motion
//-tc-	TallComponents


// https://drafts.csswg.org/selectors-4/
// https://www.w3.org/TR/?tag=css&status=rec&version=latest
// https://www.w3.org/Style/CSS/all-properties.en.html
// https://www.tutorialrepublic.com/css-reference/css3-properties.php
// https://developer.mozilla.org/ru/docs/Web/CSS/%D0%9F%D1%81%D0%B5%D0%B2%D0%B4%D0%BE-%D0%BA%D0%BB%D0%B0%D1%81%D1%81%D1%8B
// https://www.smashingmagazine.com/2016/05/an-ultimate-guide-to-css-pseudo-classes-and-pseudo-elements/#backdrop-experimental
// https://www.tutorialrepublic.com/css-reference/css3-properties.php
// https://www.hostinger.com/tutorials/css-cheat-sheet


Predefined::Predefined() {

//PREDEFINED KEYWORDS

//  initial - represents the value specified as the property’s initial value
//  inherit - represents the computed value of the property on the element’s parent
//  unset - acts as either inherit or initial, depending on whether the property is inherited or not




//    ns|* - вхождения всех элементов в пространстве имён ns
//    *|* - находит все элементы
//    |* - ищет все элементы без объявленного пространства имён
//    * - находит все элементы


//    element { style properties }

//    .classname { style properties }
//    [class~=classname] { style properties }


//    #id_value { style properties }
//    [id=id_value] { style properties }

//    former_element + target_element { style properties } // селектор смежного или след елемента
//    element ~ element { style properties } // селектор след елемента
//    selector1 > selector2 { style properties } // селектор дочерних елементов
//    selector1 selector2 { style properties } // селектор потомков
//    column-selector || cell-selector { style properties } // селектор с првязкой к объекту в таблице

//    [attr]
//        Обозначает элемент с атрибутом по имени attr.
//    [attr=value]
//        Обозначает элемент с именем атрибута attr и значением в точности сопадающим с value.
//    [attr~=value]
//        Обозначает элемент с именем атрибута attr значением которого является набор слов разделенных пробелами, одно из которых в точности равно value
//    [attr|=value]
//        Обозначает элемент с именем атрибута attr. Его значение при этом может быть или в точности равно "value" или может начинаться с "value" со сразу же следующим "-" (U+002D). Это может быть использовано когда язык описывается с подкодом.
//    [attr^=value]
//        Обозначает элемент с именем атрибута attr значение которого начинается с "value"
//    [attr$=value]
//        Обозначает элемент с именем атрибута attr чье значение заканчивается на "value"
//    [attr*=value]
//        Обозначает элемент с именем атрибута attr чье значение содержит по крайней мере одно вхождение строки "value" как подстроки.




//UNITS

//    cm 	centimeters 	1cm = 96px/2.54
//    mm 	millimeters 	1mm = 1/10th of 1cm
//    Q 	quarter-millimeters 	1Q = 1/40th of 1cm
//    in 	inches 	1in = 2.54cm = 96px
//    pc 	picas 	1pc = 1/6th of 1in
//    pt 	points 	1pt = 1/72th of 1in
//    px 	pixels 	1px = 1/96th of 1in



//  px
//  % - процент от значения свойства родителя
//  rem - размер относительно размера шрифта элемента <html>
//  1mm (мм) = 3.8px
//  1cm (см) = 38px
//  1pt (типографский пункт) = 4/3px
//  1pc (типографская пика) = 16px
//  1in - 2.54 centimeters (96,52px)
//  1q - quarter-millimeters (1/40th of 1cm)

//  1em – текущий размер шрифта.
//  1ex - размер символа "x"
//  1ch - размер символа "0"
//  1ic - размер символа "水" (CJK water ideograph, U+6C34) glyph
//  cap - nominal height of capital letters of the element’s font

//  lh - line height of the element
//  rlh - line height of the root element
//  1vw - Equal to 1% of the width of the initial containing block.
//  1vh - Equal to 1% of the height of the initial containing block.
//  1vi - Equal to 1% of the size of the initial containing block in the direction of the root element’s inline axis.
//  1vb - Equal to 1% of the size of the initial containing block in the direction of the root element’s block axis.
//  vmin – наименьшее из (vw, vh), в IE9 обозначается vm
//  vmax – наибольшее из (vw, vh)

//  gd - the grid defined by 'layout-grid' // p { layout-grid: strict both 20pt 15pt; margin: 1gd 3gd 1gd 2gd }


//    deg
//        Degrees. There are 360 degrees in a full circle.
//    grad
//        Gradians, also known as "gons" or "grades". There are 400 gradians in a full circle.
//    rad
//        Radians. There are 2π radians in a full circle.
//    turn
//        Turns. There is 1 turn in a full circle.


//    Hz
//        Hertz. It represents the number of occurrences per second.
//    kHz
//        KiloHertz. A kiloHertz is 1000 Hertz.


//    s
//        Seconds.
//    ms
//        Milliseconds. There are 1000 milliseconds in a second.


//    dpi
//        Dots per inch.
//    dpcm
//        Dots per centimeter.
//    dppx, x
//        Dots per px unit.


// FUNCS

//    'attr(' ident [ ',' <type> [ ',' <value> ]? ]? ')'

// url()
// rgba()
// attr() // is allowed as a component value in properties applied to an element or pseudo-element
// calc()
// min()
// max()
// clamp() // represents its central calculation, clamped according to its min and max calculations
// toggle() // expression allows descendant elements to cycle over a list of values instead of inheriting the same value.


// linear-gradient()
// radial-gradient()
// repeating-linear-gradient()
// repeating-radial-gradient()


//TAGS


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


//  PROPERTIES

//    A
//    align-content 	Specifies the alignment between the lines inside a flexible container when the items do not use all available space
//    align-items 	Specifies the alignment for items inside a flexible container
//    align-self 	Specifies the alignment for selected items inside a flexible container
//    all 	Resets all properties (except unicode-bidi and direction)
//    animation 	A shorthand property for all the animation-* properties
//    animation-delay 	Specifies a delay for the start of an animation
//    animation-direction 	Specifies whether an animation should be played forwards, backwards or in alternate cycles
//    animation-duration 	Specifies how long an animation should take to complete one cycle
//    animation-fill-mode 	Specifies a style for the element when the animation is not playing (before it starts, after it ends, or both)
//    animation-iteration-count 	Specifies the number of times an animation should be played
//    animation-name 	Specifies a name for the @keyframes animation
//    animation-play-state 	Specifies whether the animation is running or paused
//    animation-timing-function 	Specifies the speed curve of an animation

//    B
//    backface-visibility 	Defines whether or not the back face of an element should be visible when facing the user
//    background 	A shorthand property for all the background-* properties
//    background-attachment 	Sets whether a background image scrolls with the rest of the page, or is fixed
//    background-blend-mode 	Specifies the blending mode of each background layer (color/image)
//    background-clip 	Defines how far the background (color or image) should extend within an element
//    background-color 	Specifies the background color of an element
//    background-image 	Specifies one or more background images for an element
//    background-origin 	Specifies the origin position of a background image
//    background-position 	Specifies the position of a background image
//    background-repeat 	Sets if/how a background image will be repeated
//    background-size 	Specifies the size of the background images
//    border 	A shorthand property for border-width, border-style and border-color
//    border-bottom 	A shorthand property for border-bottom-width, border-bottom-style and border-bottom-color
//    border-bottom-color 	Sets the color of the bottom border
//    border-bottom-left-radius 	Defines the radius of the border of the bottom-left corner
//    border-bottom-right-radius 	Defines the radius of the border of the bottom-right corner
//    border-bottom-style 	Sets the style of the bottom border
//    border-bottom-width 	Sets the width of the bottom border
//    border-collapse 	Sets whether table borders should collapse into a single border or be separated
//    border-color 	Sets the color of the four borders
//    border-image 	A shorthand property for all the border-image-* properties
//    border-image-outset 	Specifies the amount by which the border image area extends beyond the border box
//    border-image-repeat 	Specifies whether the border image should be repeated, rounded or stretched
//    border-image-slice 	Specifies how to slice the border image
//    border-image-source 	Specifies the path to the image to be used as a border
//    border-image-width 	Specifies the width of the border image
//    border-left 	A shorthand property for all the border-left-* properties
//    border-left-color 	Sets the color of the left border
//    border-left-style 	Sets the style of the left border
//    border-left-width 	Sets the width of the left border
//    border-radius 	A shorthand property for the four border-*-radius properties
//    border-right 	A shorthand property for all the border-right-* properties
//    border-right-color 	Sets the color of the right border
//    border-right-style 	Sets the style of the right border
//    border-right-width 	Sets the width of the right border
//    border-spacing 	Sets the distance between the borders of adjacent cells
//    border-style 	Sets the style of the four borders
//    border-top 	A shorthand property for border-top-width, border-top-style and border-top-color
//    border-top-color 	Sets the color of the top border
//    border-top-left-radius 	Defines the radius of the border of the top-left corner
//    border-top-right-radius 	Defines the radius of the border of the top-right corner
//    border-top-style 	Sets the style of the top border
//    border-top-width 	Sets the width of the top border
//    border-width 	Sets the width of the four borders
//    bottom 	Sets the elements position, from the bottom of its parent element
//    box-decoration-break 	Sets the behavior of the background and border of an element at page-break, or, for in-line elements, at line-break.
//    box-shadow 	Attaches one or more shadows to an element
//    box-sizing 	Defines how the width and height of an element are calculated: should they include padding and borders, or not
//    break-after 	Specifies the page-, column-, or region-break behavior after the generated box
//    break-before 	Specifies the page-, column-, or region-break behavior before the generated box
//    break-inside 	Specifies the page-, column-, or region-break behavior inside the generated box

//    C
//    caption-side 	Specifies the placement of a table caption
//    caret-color 	Specifies the color of the cursor (caret) in inputs, textareas, or any element that is editable
//    @charset 	Specifies the character encoding used in the style sheet
//    clear 	Specifies on which sides of an element floating elements are not allowed to float
//    clip 	Clips an absolutely positioned element
//    color 	Sets the color of text
//    column-count 	Specifies the number of columns an element should be divided into
//    column-fill 	Specifies how to fill columns, balanced or not
//    column-gap 	Specifies the gap between the columns
//    column-rule 	A shorthand property for all the column-rule-* properties
//    column-rule-color 	Specifies the color of the rule between columns
//    column-rule-style 	Specifies the style of the rule between columns
//    column-rule-width 	Specifies the width of the rule between columns
//    column-span 	Specifies how many columns an element should span across
//    column-width 	Specifies the column width
//    columns 	A shorthand property for column-width and column-count
//    content 	Used with the :before and :after pseudo-elements, to insert generated content
//    counter-increment 	Increases or decreases the value of one or more CSS counters
//    counter-reset 	Creates or resets one or more CSS counters
//    cursor 	Specifies the mouse cursor to be displayed when pointing over an element

//    D
//    direction 	Specifies the text direction/writing direction
//    display 	Specifies how a certain HTML element should be displayed

//    E
//    empty-cells 	Specifies whether or not to display borders and background on empty cells in a table

//    F
//    filter 	Defines effects (e.g. blurring or color shifting) on an element before the element is displayed
//    flex 	A shorthand property for the flex-grow, flex-shrink, and the flex-basis properties
//    flex-basis 	Specifies the initial length of a flexible item
//    flex-direction 	Specifies the direction of the flexible items
//    flex-flow 	A shorthand property for the flex-direction and the flex-wrap properties
//    flex-grow 	Specifies how much the item will grow relative to the rest
//    flex-shrink 	Specifies how the item will shrink relative to the rest
//    flex-wrap 	Specifies whether the flexible items should wrap or not
//    float 	Specifies whether or not a box should float
//    font 	A shorthand property for the font-style, font-variant, font-weight, font-size/line-height, and the font-family properties
//    @font-face 	A rule that allows websites to download and use fonts other than the "web-safe" fonts
//    font-family 	Specifies the font family for text
//    font-feature-settings 	Allows control over advanced typographic features in OpenType fonts
//    @font-feature-values 	Allows authors to use a common name in font-variant-alternate for feature activated differently in OpenType
//    font-kerning 	Controls the usage of the kerning information (how letters are spaced)
//    font-language-override 	Controls the usage of language-specific glyphs in a typeface
//    font-size 	Specifies the font size of text
//    font-size-adjust 	Preserves the readability of text when font fallback occurs
//    font-stretch 	Selects a normal, condensed, or expanded face from a font family
//    font-style 	Specifies the font style for text
//    font-synthesis 	Controls which missing typefaces (bold or italic) may be synthesized by the browser
//    font-variant 	Specifies whether or not a text should be displayed in a small-caps font
//    font-variant-alternates 	Controls the usage of alternate glyphs associated to alternative names defined in @font-feature-values
//    font-variant-caps 	Controls the usage of alternate glyphs for capital letters
//    font-variant-east-asian 	Controls the usage of alternate glyphs for East Asian scripts (e.g Japanese and Chinese)
//    font-variant-ligatures 	Controls which ligatures and contextual forms are used in textual content of the elements it applies to
//    font-variant-numeric 	Controls the usage of alternate glyphs for numbers, fractions, and ordinal markers
//    font-variant-position 	Controls the usage of alternate glyphs of smaller size positioned as superscript or subscript regarding the baseline of the font
//    font-weight 	Specifies the weight of a font

//    G
//    grid 	A shorthand property for the grid-template-rows, grid-template-columns, grid-template-areas, grid-auto-rows, grid-auto-columns, and the grid-auto-flow properties
//    grid-area 	Either specifies a name for the grid item, or this property is a shorthand property for the grid-row-start, grid-column-start, grid-row-end, and grid-column-end properties
//    grid-auto-columns 	Specifies a default column size
//    grid-auto-flow 	Specifies how auto-placed items are inserted in the grid
//    grid-auto-rows 	Specifies a default row size
//    grid-column 	A shorthand property for the grid-column-start and the grid-column-end properties
//    grid-column-end 	Specifies where to end the grid item
//    grid-column-gap 	Specifies the size of the gap between columns
//    grid-column-start 	Specifies where to start the grid item
//    grid-gap 	A shorthand property for the grid-row-gap and grid-column-gap properties
//    grid-row 	A shorthand property for the grid-row-start and the grid-row-end properties
//    grid-row-end 	Specifies where to end the grid item
//    grid-row-gap 	Specifies the size of the gap between rows
//    grid-row-start 	Specifies where to start the grid item
//    grid-template 	A shorthand property for the grid-template-rows, grid-template-columns and grid-areas properties
//    grid-template-areas 	Specifies how to display columns and rows, using named grid items
//    grid-template-columns 	Specifies the size of the columns, and how many columns in a grid layout
//    grid-template-rows 	Specifies the size of the rows in a grid layout

//    H
//    hanging-punctuation 	Specifies whether a punctuation character may be placed outside the line box
//    height 	Sets the height of an element
//    hyphens 	Sets how to split words to improve the layout of paragraphs

//    I
//    image-orientation Provides a way to apply an "out-of-band" rotation to image source data to correctly orient an image.
//          Initial: from-image
//                none
//                    No additional rotation is applied: the image is oriented as encoded.
//                from-image
//                    If the image has an orientation specified in its metadata, such as EXIF, this value computes to the angle that the metadata specifies is necessary to correctly orient the image. If necessary, this angle is then rounded and normalized as described above for an <angle> value. If there is no orientation specified in its metadata, this value computes to none.
//                <angle>
//                    Positive values cause the image to be rotated to the right (in a clockwise direction), while negative values cause a rotation to the left. The computed value of the property is calculated by moduloing the value by 1turn (so that it lies in the half-open range [0turn, 1turn)), then rounding it to the nearest quarter-turn, rounding away from 0 (so 45deg rounds to 90deg, etc).
//                <angle>? flip
//                    Identical to the plain <angle> case, except that after rotation the image is flipped horizontally. If the <angle> is omitted, it defaults to 0deg.
//    image-rendering 	Gives a hint to the browser about what aspects of an image are most important to preserve when the image is scaled
//          This property does not dictate any particular scaling algorithm to be used. For example, with image-rendering: auto, a user agent might scale images with bilinear interpolation by default, switch to nearest-neighbor interpolation in high-load situations, and switch to a high-quality scaling algorithm like Lanczos interpolation for static images that aren’t moving or changing. Similarly, with 'image-rendering: crisp-edges', a user agent might scale images with nearest-neighbor interpolation by default, and switch to EPX interpolation in low-load situations.
//          Initial: auto
//                auto
//                    The scaling algorithm is UA dependent.
//                smooth
//                    The image should be scaled with an algorithm that maximizes the appearance of the image. In particular, scaling algorithms that "smooth" colors are acceptable, such as bilinear interpolation. This is intended for images such as photos.
//                high-quality
//                    Identical to smooth, but with a preference for higher-quality scaling. If system resources are constrained, images with high-quality should be prioritized over those with any other value, when considering which images to degrade the quality of and to what degree.
//                    This value does not prevent the image quality from being degraded when the system resources are constrained. It merely expresses a preference that these images should receive extra scaling resources relative to the auto images. If all images on the page have high-quality applied, it’s equivalent to all of them having auto applied—they’re all treated the same.

//                    To get the most value out of high-quality, only apply it to the most important images on the page.
//                crisp-edges
//                    The image must be scaled with an algorithm that preserves contrast and edges in the image, and which does not smooth colors or introduce blur to the image in the process. This is intended for images such as pixel art or line drawings.
//                pixelated
//                    The image must be scaled with the "nearest neighbor" or similar algorithm, to preserve a "pixelated" look as the image changes in size.


//    @import 	Allows you to import a style sheet into another style sheet
//    isolation 	Defines whether an element must create a new stacking content

//    J
//    justify-content 	Specifies the alignment between the items inside a flexible container when the items do not use all available space

//    K
//    @keyframes 	Specifies the animation code

//    L
//    left 	Specifies the left position of a positioned element
//    letter-spacing 	Increases or decreases the space between characters in a text
//    line-break 	Specifies how/if to break lines
//    line-height 	Sets the line height
//    list-style 	Sets all the properties for a list in one declaration
//    list-style-image 	Specifies an image as the list-item marker
//    list-style-position 	Specifies the position of the list-item markers (bullet points)
//    list-style-type 	Specifies the type of list-item marker

//    M
//    margin 	Sets all the margin properties in one declaration
//    margin-bottom 	Sets the bottom margin of an element
//    margin-left 	Sets the left margin of an element
//    margin-right 	Sets the right margin of an element
//    margin-top 	Sets the top margin of an element
//    max-height 	Sets the maximum height of an element
//    max-width 	Sets the maximum width of an element
//    @media 	Sets the style rules for different media types/devices/sizes
//    min-height 	Sets the minimum height of an element
//    min-width 	Sets the minimum width of an element
//    mix-blend-mode 	Specifies how an element's content should blend with its direct parent background

//    O
//    object-fit 	Specifies how the contents of a replaced element should be fitted to the box established by its used height and width
//          // data:image/png;base64,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
//          // Initial: 	fill
//                fill
//                    The replaced content is sized to fill the element’s content box: the object’s concrete object size is the element’s used width and height.
//                contain
//                    The replaced content is sized to maintain its aspect ratio while fitting within the element’s content box: its concrete object size is resolved as a contain constraint against the element’s used width and height.
//                cover
//                    The replaced content is sized to maintain its aspect ratio while filling the element’s entire content box: its concrete object size is resolved as a cover constraint against the element’s used width and height.
//                none
//                    The replaced content is not resized to fit inside the element’s content box: determine the object’s concrete object size using the default sizing algorithm with no specified size, and a default object size equal to the replaced element’s used width and height.
//                scale-down
//                    Size the content as if none or contain were specified, whichever would result in a smaller concrete object size.

//    object-position 	Specifies the alignment of the replaced element inside its box
            // Initial:  	50% 50%


//    opacity 	Sets the opacity level for an element
//    order 	Sets the order of the flexible item, relative to the rest
//    orphans 	Sets the minimum number of lines that must be left at the bottom of a page when a page break occurs inside an element
//    outline 	A shorthand property for the outline-width, outline-style, and the outline-color properties
//    outline-color 	Sets the color of an outline
//    outline-offset 	Offsets an outline, and draws it beyond the border edge
//    outline-style 	Sets the style of an outline
//    outline-width 	Sets the width of an outline
//    overflow
//        Specifies what happens if content overflows an element's box
//    overflow-wrap 	Specifies whether or not the browser may break lines within words in order to prevent overflow (when a string is too long to fit its containing box)
//    overflow-x 	Specifies whether or not to clip the left/right edges of the content, if it overflows the element's content area
//    overflow-y 	Specifies whether or not to clip the top/bottom edges of the content, if it overflows the element's content area

//    P
//    padding 	A shorthand property for all the padding-* properties
//    padding-bottom 	Sets the bottom padding of an element
//    padding-left 	Sets the left padding of an element
//    padding-right 	Sets the right padding of an element
//    padding-top 	Sets the top padding of an element
//    page-break-after 	Sets the page-break behavior after an element
//    page-break-before 	Sets the page-break behavior before an element
//    page-break-inside 	Sets the page-break behavior inside an element
//    perspective 	Gives a 3D-positioned element some perspective
//    perspective-origin 	Defines at which position the user is looking at the 3D-positioned element
//    pointer-events 	Defines whether or not an element reacts to pointer events
//    position 	Specifies the type of positioning method used for an element (static, relative, absolute or fixed)

//    Q
//    quotes 	Sets the type of quotation marks for embedded quotations

//    R
//    resize 	Defines if (and how) an element is resizable by the user
//    right 	Specifies the right position of a positioned element

//    S
//    scroll-behavior 	Specifies whether to smoothly animate the scroll position in a scrollable box, instead of a straight jump

//    T
//    tab-size 	Specifies the width of a tab character
//    table-layout 	Defines the algorithm used to lay out table cells, rows, and columns
//    text-align 	Specifies the horizontal alignment of text
//    text-align-last 	Describes how the last line of a block or a line right before a forced line break is aligned when text-align is "justify"
//    text-combine-upright 	Specifies the combination of multiple characters into the space of a single character
//    text-decoration 	Specifies the decoration added to text
//    text-decoration-color 	Specifies the color of the text-decoration
//    text-decoration-line 	Specifies the type of line in a text-decoration
//    text-decoration-style 	Specifies the style of the line in a text decoration
//    text-indent 	Specifies the indentation of the first line in a text-block
//    text-justify 	Specifies the justification method used when text-align is "justify"
//    text-orientation 	Defines the orientation of the text in a line
//    text-overflow 	Specifies what should happen when text overflows the containing element
//    text-shadow 	Adds shadow to text
//    text-transform 	Controls the capitalization of text
//    text-underline-position 	Specifies the position of the underline which is set using the text-decoration property
//    top 	Specifies the top position of a positioned element
//    transform 	Applies a 2D or 3D transformation to an element
//    transform-origin 	Allows you to change the position on transformed elements
//    transform-style 	Specifies how nested elements are rendered in 3D space
//    transition 	A shorthand property for all the transition-* properties
//    transition-delay 	Specifies when the transition effect will start
//    transition-duration 	Specifies how many seconds or milliseconds a transition effect takes to complete
//    transition-property 	Specifies the name of the CSS property the transition effect is for
//    transition-timing-function 	Specifies the speed curve of the transition effect

//    U
//    unicode-bidi 	Used together with the direction property to set or return whether the text should be overridden to support multiple languages in the same document
//    user-select 	Specifies whether the text of an element can be selected

//    V
//    vertical-align 	Sets the vertical alignment of an element
//    visibility 	Specifies whether or not an element is visible

//    W
//    white-space 	Specifies how white-space inside an element is handled
//    widows 	Sets the minimum number of lines that must be left at the top of a page when a page break occurs inside an element
//    width 	Sets the width of an element
//    word-break 	Specifies how words should break when reaching the end of a line
//    word-spacing 	Increases or decreases the space between words in a text
//    word-wrap 	Allows long, unbreakable words to be broken and wrap to the next line
//    writing-mode 	Specifies whether lines of text are laid out horizontally or vertically

//    Z
//    z-index 	Sets the stack order of a positioned element


//    Pseudo-classes

//        :active                               // Selects the active element
//        :after                                // Insert something after the content of a element
//        :any()
//        :any-link
//        :before                               // Insert something before the content of a element
//        :blank
//        :checked                              // Selects every checked element
//        :default
//        :defined
//        :dir()                                // ***Experimental. // Selects every elements whose directionality (dir prop) is specified in the document
//        :disabled                             // Selects every disabled element
//        :empty                                // Selects every element that has no children
//        :enabled                              // Selects every enabled element
//        :first
//        :first-line // possibly outdated
//        :first-letter // possibly outdated
//        :first-child                          // Selects every elements that is the first child of its parent
//        :first-of-type                        // Selects every element that is the first element of its parent and has the same type
//        :fullscreen                           // Selects every elements that are displayed in full-screen mode.
//        :focus                                // Selects the element that has focus
//        :focus-visible
//        :focus-within
//        :fullscreen                           // ***Experimental.
//        :has()
//        :host()
//        :host-context()
//        :hover                                // Selects element on mouse over
//        :indeterminate
//        :in-range                             // Selects elements with a value within a specified range
//        :indeterminate
//        :invalid                              // Selects all elements with an invalid value
//        :is()
//        :lang()                               // Selects every element with a lang attribute value starting with parameter
//        :last-child                           // Selects every elements that is the last child of its parent
//        :last-of-type                         // Selects every element that is the last element of its parent with the same type
//        :left
//        :link                                 // Selects all unvisited elements (links)
//        :matches()
//        :not()                                // Selects every element that is not respond to selector parameter
//        :nth-child()                          // Selects every element that is the n-param child of its parent
//        :nth-last-child()                     // Selects every element that is the n-param child of its parent, counting from the last child
//        :nth-last-of-type()                   // Selects every element that is the n-param element of its parent with the same type, counting from the last child
//        :nth-of-type()                        // Selects every element that is the n-param element of its parent with the same type
//        :only-child                           // Selects every element that is the only child of its parent
//        :only-of-type                         // Selects every element that is the has predefined type
//        :optional                             // Selects elements with no "required" attribute
//        :out-of-range                         // Selects elements with a value outside a specified range
//        :placeholder                          // ***Experimental.
//        :placeholder-shown
//        :read-only                            // Selects elements with a "readonly" attribute specified
//        :read-write                           // Selects elements with no "readonly" attribute
//        :required                             // Selects elements with a "required" attribute specified
//        :right
//        :root                                 // Selects the document's root element
//        :scope                                // ***Experimental. // Makes most sense when it’s tied to the scoped HTML attribute in a style tag. If there is no scoped attribute in a style tag within a section of the page, then the :scope pseudo-class will traverse all the way up to the html element, which is basically the default scope of a style sheet.
//        :target                               // Selects the current active #anchor element (clicked on a URL containing that anchor name)
//        :valid                                // Selects all elements with a valid value
//        :visited                              // Selects all visited links
//        :where()

//    Pseudo-elements

//        ::-moz-progress-bar
//        ::-moz-range-progress
//        ::-moz-range-thumb
//        ::-moz-range-track
//        ::-ms-browse
//        ::-ms-check
//        ::-ms-clear
//        ::-ms-expand
//        ::-ms-fill
//        ::-ms-fill-lower
//        ::-ms-fill-upper
//        ::-ms-reveal
//        ::-ms-thumb
//        ::-ms-ticks-after
//        ::-ms-ticks-before
//        ::-ms-tooltip
//        ::-ms-track
//        ::-ms-value
//        ::-webkit-progress-bar
//        ::-webkit-progress-value
//        ::-webkit-slider-runnable-track
//        ::-webkit-slider-thumb                // Represents the "thumb" that the user can move within the "groove" of an <input> of type="range" to alter its numerical value.
//        ::after                               // Insert something after the content of a element
//        ::backdrop                            // ***Experimental. // box the size of the viewport which is rendered immediately beneath any element being presented in full-screen mode. This includes both elements which have been placed in full-screen mode using the Fullscreen API and <dialog> elements.
//        ::before                              // Insert something before the content of a element
//        ::cue                                 // Matches WebVTT cues within a selected element. This can be used to style captions and other cues in media with VTT tracks.
//            Has limits by next properties:
//                background and its longhand properties
//                color
//                font and its longhand properties
//                line-height
//                opacity
//                outline and its longhand properties
//                ruby-position
//                text-combine-upright
//                text-decoration and its longhand properties
//                text-shadow
//                visibility
//                white-space
//        ::explainer
//        ::first-letter                        // Selects the first letter of a element
//        ::first-line                          // Selects the first line of a element
//        ::grammar-error                       // ***Experimental. Represents a text segment which the user agent has flagged as grammatically incorrect.
//        ::marker                              // ***Experimental. Selects the marker box of a list item, which typically contains a bullet or number. It works on any element or pseudo-element set to display: list-item, such as the <li> and <summary> elements.
//        ::part()                              // ***Experimental. Represents any element within a shadow tree that has a matching part attribute.
//        ::placeholder                         // Insert placeholder text to elements
//        ::selection                           // Selects the portion of an element that is selected by a user
//        ::slotted()                           // Represents any element that has been placed into a slot inside an HTML template
//        ::spelling-error                      // ***Experimental. Represents a text segment which the user agent has flagged as incorrectly spelled
//        ::theme







//    keys.insert(QByteArrayLiteral("#{"), lex_interpolation);
}


bool Predefined::hasKey(const QByteArray & key) { return keys.contains(key); }
StateLexem Predefined::lexem(const QByteArray & key) {
    return keys.value(key, lex_word);
}
