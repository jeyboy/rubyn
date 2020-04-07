# BACKSLASH NOTATIONS

'\n' #  newline (0x0a)
'\s' #  space (0x20)
'\r' #  carriage return (0x0d)
'\t' #  tab (0x09)
'\v' #  vertical tab (0x0b)
'\f' #  formfeed (0x0c)
'\b' #  backspace (0x08)
'\a' #  bell/alert (0x07)
'\e' #  escape (0x1b)
'\nnn' #  character with octal value nnn
'\xnn'   # character with hexadecimal value nn
'\unnnn' #  Unicode code point U+nnnn (Ruby 1.9 and later)
'\u{nnnnn}' #   Unicode code point U+nnnnn with more than four hex digits must be enclosed in curly braces
'\cx' #  control-x
'\C-x' #   control-x
'\M-x' #   meta-x
'\M-\C-x' #  meta-control-x
'\x' #  character x itself (for example \" is the double quote character)


# RECOG

a + b # is interpreted as a+b ( Here a is a local variable)
a  +b # is interpreted as a(+b) ( Here a is a method call)

p ?a # char sequence
1 + ?a # char sequence
1 (?a) # char sequence
1 [?a] # char sequence
a:?a  # char sequence
'' ?a # ternar
1?a # ternar
1 ?a # ternar
(1) ?a # ternar
[1] ?a # ternar

a(/b/) # reg expression
p[/a/] # reg expression
a /n/ # reg expression
/an/ # reg expression
{ with: /\A([^@\s\]\[\)\(\}\{]+)@((?:[-a-z0-9]+\.)+[a-z]{2,})\z/i } # reg expression
1 /3 # division
'1' /3 # division
(a) /3 # division
a/n/ # division
a/ b/ # division
a / b # division

#SELF INJECTION

"Hello".try { |str| str + " World" } #=> "Hello World" # Rails try
nil.yield_self { |obj| "Hello World" } #=> "Hello World" # ruby 2.5+ method
"Hello".tap { |str| str + " World" } #=> "Hello"


add_greeting = -> (str) { "HELLO " + str }
to_upper = -> (str) { str.upcase }

# with new `yield_self`
"world".yield_self(&to_upper).yield_self(&add_greeting) #=> "HELLO WORLD"

# nested function calls
add_greeting.call(to_upper.call("world")) #=> "HELLO WORLD"


# PERCENT STRING

# Besides %(...) which creates a String, The % may create other types of object. As with strings, an uppercase letter allows interpolation and escaped characters while a lowercase letter disables them.

# These are the types of percent strings in ruby:

# %i Non-interpolated Array of symbols, separated by whitespace
# %l Interpolated Array of symbols, separated by whitespace
# %q String
# %Q String with interpolation
# %/ String with interpolation
# %r Regular Expression
# %s Symbol
# %w Array of Strings
# %W Array of double quoted strings
# %x Backtick (capture subshell result)


%Q(Joe said: "Frank said: "#{what_frank_said}"") #=> "Joe said: "Frank said: "Hello!"""
%/Joe said: "Frank said: "#{what_frank_said}""/
%{Ruby is fun.} #  equivalent to "Ruby is fun."
%q(Joe said: 'Frank said: '#{what_frank_said} ' ') #=> "Joe said: 'Frank said: '\#{what_frank_said} ' '"
%W(#{foo} Bar Bar\ with\ space)#=> ["Foo", "Bar", "Bar with space"]
%w(#{foo} Bar Bar\ with\ space) #=> ["\#{foo}", "Bar", "Bar with space"]
%x(echo foo:#{foo}) #=> "foo:Foo\n"
%r(/home/#{foo}) #=> "/\\/home\\/Foo/"

%s(foo) #=> :foo
%s(foo bar) #=> :"foo bar"
%s(#{foo} bar) #=> :"\#{foo} bar"


# For the two array forms of percent string, if you wish to include a space in one of the array entries you must escape it with a ?\? character:

%w[one one-hundred\ one] #=> ["one", "one-hundred one"]

#If you are using ?(?, ?[?, ?{?, ?<? you must close it with ?)?, ?]?, ?}?, ?>? respectively. You may use most other non-alphanumeric characters for percent string delimiters such as ?%?, ?|?, ?^?, etc.

%Q!Joe said: "Frank said: "#{what_frank_said}""!
%Q[Joe said: "Frank said: "#{what_frank_said}""]
%Q+Joe said: "Frank said: "#{what_frank_said}""+

"con" "cat" "en" "at" "ion" #=> "concatenation"
"This string contains " "no newlines."              #=> "This string contains no newlines."

# Any combination of adjacent single-quote, double-quote, percent strings will be concatenated as long as a percent-string is not last.

%q{a} 'b' "c" #=> "abc"
"a" 'b' %q{c} #=> NameError: uninitialized constant q

# There is also a character literal notation to represent single character strings, which syntax is a question mark (?) followed by a single character or escape sequence that corresponds to a single codepoint in the script encoding:

?a       #=> "a"
?abc     #=> SyntaxError
?\n      #=> "\n"
?\s      #=> " "
?\\      #=> "\\"
?\u{41}  #=> "A"
?\C-a    #=> "\x01"
?\M-a    #=> "\xE1"
?\M-\C-a #=> "\x81"
?\C-\M-a #=> "\x81", same as above
??      #=> "?"


# COMMENTS

# This is a comment.

=begin
This is a comment.
This is a comment, too.
This is a comment, too.
I said that already.
=end



# INTEGERS

123                  # Fixnum decimal
1_234                # Fixnum decimal with underline
-500                 # Negative Fixnum
0o377                # octal
0xff                 # hexadecimal
0b1011               # binary
?a                   # character code for 'a'
?\n                  # code for a newline (0x0a)
12345678901234567890 # Bignum
1.day        # Method call


# FLOATS

123.4                # floating point value
1.0e6                # scientific notation
4E20                 # dot not required
4e+20                # sign before exponential

+3
3.2e23
-4.70e+9
-.2E-4			#=> SyntaxError
-7.6603

# OPERATORS

# A new operator (&.)(SAFE NAVIGATION) has been introduced. It can be very useful in cases where you need to check if an object is 
# nil before calling a method on it. It will return nil if the object equals nil, otherwise it calls the method on the object.

if user && user.admin?
  # do something
end

if user&.admin?
  # do something
end



c = a + b
a, b, c = 10, 20, 30

return a,b,c,g

c += a
c -= a
c *= a
c /= a
c %= a
c **= a

a + b = 23
a - + b = -10
a - * b # error
a - b = -10
a * b = 2000
b / a = 2
b % a = 1
a**b = 8

(a == b)
(a != b)
(a > b)
(a < b)
(a >= b)
(a <= b)
(a <=> b) # Combined comparison operator. Returns 0 if first operand equals second, 1 if first operand is greater than the second and -1 if first operand is less than the second.
(1...10) === 5 # Used to test equality within a when clause of a case statement
1.eql?(1.0) == false # True if the receiver and argument have both the same type and equal values
a.equal?b # True if the receiver and argument have the same object id 

a    = 60 # 0011 1100
b    = 13 # 0000 1101
-----------------
a&b = 12 # =  0000 1100
a|b = 61 # =  0011 1101
a^b = 49 # =  0011 0001
~a = -61 # =  1100 0011
a << 2 = 240 # = 1111 0000
a >> 2 = 15 # = 0000 1111

(a and b) == true
(a or b) == true.
not(a && b) == false.
(a && b) == true.
(a || b) == true.
!(a && b) == false.


# BRANCH

# ternary
a = 1
a ? 1:2
(2 < 1)? 1:2
(2 < 1)?(3):2
(2 < 1)?{a:2}:3
a < 1 ? (1 + ert) : 2 - 3 + 2

puts soso if @cool
a = if @cool

x = 1
if x > 2
   puts "x is greater than 2"
elsif x <= 2 and x!=0
   puts "x is 1"
else
   puts "I can't guess the number"
end

if x > 2 then
   puts "x is greater than 2"
elsif x <= 2 and x!=0 then
   puts "x is 1"
end

if 1 then 2 else 3 end

$debug = 1
print "debug\n" if $debug


unless x>=2
   puts "x is less than 2"
 else
   puts "x is greater than 2"
end

$var =  1
print "2 -- Value is set\n" unless $var

$age =  5
case $age
when 0 .. 2
   puts "baby"
when 3, 4,5, 6
   puts "little child"
when 7 .. 12
   puts "child"
when 13 .. 18
   puts "youth"
else
   puts "adult"
end


# ruby 2.6

"something"
	.then {|str| str.chars.map {|x| x.ord + 1 }}
	.then {|ords| ords.map {|x| x.chr }}
	.then {|chars| chars.join } 
	.then {|str| str + "!" }
	.then {|str| str + "!" }



# STRINGS

puts 'escape using "\\"';
puts 'That\'s right';
x, y, z = 12, 36, 72
puts "The value of x is #{ x }."
puts "The sum of x and y is #{ x + y }."
puts "The average was #{ (x + y + z)/3 }."

%{Ruby is fun.} #  equivalent to "Ruby is fun."
%Q{ Ruby is fun. } # equivalent to " Ruby is fun. "
%q[Ruby is fun.] #  equivalent to a single-quoted string
%x!ls! # equivalent to back tick command output `ls`
`cd .`



# REGEXP

# Except for control characters, (+ ? . * ^ $ ( ) [ ] { } | \), all characters match themselves. 
#  You can escape a control character by preceding it with a backslash.

#Greedy: As Many As Possible (longest match)
#  By default, a quantifier tells the engine to match as many instances of its quantified 
#   token or subpattern as possible. This behavior is called greedy. 

#Lazy: As Few As Possible (shortest match)
#  In contrast to the standard greedy quantifier, which eats up as many instances of 
#   the quantified token as possible, a lazy (sometimes called reluctant) quantifier tells 
#   the engine to match as few of the quantified tokens as needed. 
#  A regular quantifier is made lazy by appending a ? question mark to it. 

#Possessive: Don't Give Up Characters (ruby 2+)
#  !No backtracking speed up work of regular expression machine.
#  In contrast to the standard quantifier, which gives up characters if needed in order to 
#   allow the rest of the pattern to match, a possessive quantifier tells the engine that even 
#   if what follows in the pattern fails to match, it will hang on to its characters. 
#  A regular quantifier is made possessive by appending a + plus mark to it. 



# re? - Matches 0 or 1 occurrence of preceding expression.
# re?? - Matches 0 or 1 occurrence of preceding expression. Lazy. 
#  /<(r??).*>/ matches "" in "<ruby>perl>"
# re?+ - Matches 0 or 1 occurrence of preceding expression. Possesive (without backtracking)

# re* - Matches 0 or more occurrences of preceding expression.
# re*? - Matches 0 or more occurrences of preceding expression. Lazy.
#  /<.*?>/ matches "<ruby>" in "<ruby>perl>"
# re*+ - Matches 0 or more occurrences of preceding expression. Possesive (without backtracking)
  

# re+ - Matches 1 or more occurrence of preceding expression.
# re+? - Matches 1 or more occurrence of preceding expression. Lazy. 
#  /<.+?>/ matches "<ruby>" in "<ruby>perl>"
# re++ - Matches 1 or more occurrence of preceding expression. Possesive (without backtracking)
#  Whereas the regex A+. matches the string "AAA", A++. doesn't.

# re{n} - Matches exactly n number of occurrences of preceding expression.
# re{n,} - Matches n or more occurrences of preceding expression.
# re{n, m} - Matches at least n and at most m occurrences of preceding expression.
# a|b - Matches either a or b.

# (re) -  Groups regular expressions and remembers matched text.
# !(re) - Not prefix. Apply rule only if text does not match pattern. 
# (?#...) Comment.
# (?imx) - Temporarily toggles on i, m, or x options within a regular expression. If in parentheses, only that area is affected.
# (?-imx) - Temporarily toggles off i, m, or x options within a regular expression. If in parentheses, only that area is affected.
# (?:re) - Groups regular expressions without remembering matched text. 
#  This is often useful when you need to group a set of constructs but don't want the group to set
#   the value of $1 or whatever.

  date = "12/25/01"
  date =~ %r{(\d+)(/|:)(\d+)(/|:)(\d+)}
  [$1,$2,$3,$4,$5] #  ?   ["12", "/", "25", "/", "01"]
  date =~ %r{(\d+)(?:/|:)(\d+)(?:/|:)(\d+)}
  [$1,$2,$3] #  ?   ["12", "25", "01"]


# (?imx:re) Temporarily toggles on i, m, or x options within parentheses.
# (?-imx:re) Temporarily toggles off i, m, or x options within parentheses.
# (?<some_name>) Link name with captured group result.
#  /\$(?<dollars>\d+)\.(?<cents>\d+)/.match("$3.67") => #<MatchData "$3.67" dollars:"3" cents:"67">
#  /\$(?<dollars>\d+)\.(?<cents>\d+)/.match("$3.67")[:dollars] #=> "3"

#  When named capture groups are used with a literal regexp on the left-hand side of an 
#   expression and the =~ operator, the captured text is also assigned to local variables 
#   with corresponding names.

  /\$(?<dollars>\d+)\.(?<cents>\d+)/ =~ "$3.67" #=> 0
  dollars #=> "3"

#  Named groups can be backreferenced with \k<name>, where name is the group name.

# (?=re) Positive lookahead assertion. Specifies position using a pattern. Doesn't have a range.
#  Matches re at this point, but does not consume it (also known charmingly as "zero-width 
#   positive lookahead"). This lets you look forward for the context of a match without affecting $&.

  str = "red, white, and blue"
  str.scan(/[a-z]+(?=,)/)   ?   ["red", "white"]


# (?<=pat) Positive lookbehind assertion: ensures that the preceding characters match pat, 
#  but doesn't include those characters in the matched text

  (?<=#START#).*?(?=#END#)


# (?!re) Negative lookahead assertion. Specifies position using pattern negation. Doesn't have a range.
#  Matches if re does not match at this point. Does not consume the match
#   (zero-width negative lookahead). 
#  For example, /hot(?!dog)(\w+)/ matches any word that contains the letters 
#   "hot" that aren't followed by "dog", returning the end of the word in $1. 


# (?<!pat) Negative lookbehind assertion: ensures that the preceding characters do not match 
#  pat, but doesn't include those characters in the matched text


# (?>re) Matches independent pattern without backtracking.
#  Nests an independent regular expression within the first regular expression. 
#  This expression is anchored at the current match position. If it consumes characters,
#     these will no longer be available to the higher-level regular expression. 
#  This construct therefore inhibits backtracking, which can be a performance enhancement. 
#  For example, the pattern /a.*b.*a/ takes exponential time when matched against a string 
#  containing an "a" followed by a number of "b"s, but with no trailing "a." 
#  However, this can be avoided by using a nested regular expression /a(?>.*b).*a/. 
#  In this form, the nested expression consumes all the the input string up to the last 
#  possible "b" character. When the check for a trailing "a" then fails, there is no need 
#  to backtrack, and the pattern match fails promptly. 

  require "benchmark"
  include Benchmark

  str = "a" + ("b" * 5000)
  bm(8) do |test|
    test.report("Normal:") { str =~ /a.*b.*a/ }
    test.report("Nested:") { str =~ /a(?>.*b).*a/ }
  end

#  produces:
#
#          user     system      total        real
#  Normal:   0.410000   0.000000   0.410000 (  0.414915)
#  Nested:   0.000000   0.000000   0.000000 (  0.001190)
#

# \nnn - 
# \xnn - 
# \cx - 
# \C-x - 
# \M-x - 
# \M-\C-x - 

# . - Matches any single character except newline. Using m option allows it to match newline as well.
# ^ - Matches beginning of line.
# $ - Matches end of line.
# \A - Matches beginning of string.
# \Z - Matches end of string. If a newline exists, it matches just before newline.
# \z - Matches end of string.
# \G - Matches point where last match finished.
# \w - Matches word characters. Equivalent to [A-Za-z0-9_].
# \W - Matches nonword characters. Equivalent to [^A-Za-z0-9_].
# \s - Matches any whitespace. Equivalent to [\t\n\r\f].
# \S - Matches any nonwhitespace. Equivalent to [^\t\n\r\f].
# \d - Matches digits. Equivalent to [0-9].
# \D - Matches nondigits. Equivalent to [^0-9].
# \h - Matches hexdigit character. Equivalent to [0-9a-fA-F].
# \H - Matches any non-hexdigit character. Equivalent to [^0-9a-fA-F].
# \b - Matches word boundaries when outside brackets. Matches backspace (0x08) when inside brackets.
# \B - Matches non-word boundaries.
# \n, \t, etc. - Matches newlines, carriage returns, tabs, etc.
# \k - backreference on a named group
#   Note: A regexp can't use named backreferences and numbered backreferences simultaneously.

  /(?<vowel>[aeiou]).\k<vowel>.\k<vowel>/.match('ototomy') #=> #<MatchData "ototo" vowel:"o">
# \g - Matches the previous subexpression named name, which can be a group name or number, again. 
#   This differs from backreferences in that it re-executes the group rather than simply 
#    trying to re-match the same text.

/\A(?<paren>\(\g<paren>*\))*\z/ =~ '()'
/\A(?<paren>\(\g<paren>*\))*\z/ =~ '(())' #=> 0

# \u - Matches unicode sequence
  /\s\u{6771 4eac 90fd}/.match("Go to ???") #=> #<MatchData " ???">

# \p - construct matches characters with the named property, much like POSIX bracket classes.
#       /\p{Alnum}/ - Alphabetic and numeric character
#       /\p{Alpha}/ - Alphabetic character
#       /\p{Blank}/ - Space or tab
#       /\p{Cntrl}/ - Control character
#       /\p{Digit}/ - Digit
#       /\p{Graph}/ - Non-blank character (excludes spaces, control characters, and similar)
#       /\p{Lower}/ - Lowercase alphabetical character
#       /\p{Print}/ - Like \p{Graph}, but includes the space character
#       /\p{Punct}/ - Punctuation character
#       /\p{Space}/ - Whitespace character ([:blank:], newline, carriage return, etc.)
#       /\p{Upper}/ - Uppercase alphabetical
#       /\p{XDigit}/ - Digit allowed in a hexadecimal number (i.e., 0-9a-fA-F)
#       /\p{Word}/ - A member of one of the following Unicode general category Letter, Mark, Number, Connector_Punctuation
#       /\p{ASCII}/ - A character in the ASCII character set
#       /\p{Any}/ - Any Unicode character (including unassigned characters)
#       /\p{Assigned}/ - An assigned character

#   A Unicode character's General Category value can also be matched with \p{Ab} where Ab 
#    is the category's abbreviation as described below:

#       /\p{L}/ - 'Letter'
#       /\p{Ll}/ - 'Letter: Lowercase'
#       /\p{Lm}/ - 'Letter: Mark'
#       /\p{Lo}/ - 'Letter: Other'
#       /\p{Lt}/ - 'Letter: Titlecase'
#       /\p{Lu}/ - 'Letter: Uppercase
#       /\p{Lo}/ - 'Letter: Other'
#       /\p{M}/ - 'Mark'
#       /\p{Mn}/ - 'Mark: Nonspacing'
#       /\p{Mc}/ - 'Mark: Spacing Combining'
#       /\p{Me}/ - 'Mark: Enclosing'
#       /\p{N}/ - 'Number'
#       /\p{Nd}/ - 'Number: Decimal Digit'
#       /\p{Nl}/ - 'Number: Letter'
#       /\p{No}/ - 'Number: Other'
#       /\p{P}/ - 'Punctuation'
#       /\p{Pc}/ - 'Punctuation: Connector'
#       /\p{Pd}/ - 'Punctuation: Dash'
#       /\p{Ps}/ - 'Punctuation: Open'
#       /\p{Pe}/ - 'Punctuation: Close'
#       /\p{Pi}/ - 'Punctuation: Initial Quote'
#       /\p{Pf}/ - 'Punctuation: Final Quote'
#       /\p{Po}/ - 'Punctuation: Other'
#       /\p{S}/ - 'Symbol'
#       /\p{Sm}/ - 'Symbol: Math'
#       /\p{Sc}/ - 'Symbol: Currency'
#       /\p{Sk}/ - 'Symbol: Modifier'
#       /\p{So}/ - 'Symbol: Other'
#       /\p{Z}/ - 'Separator'
#       /\p{Zs}/ - 'Separator: Space'
#       /\p{Zl}/ - 'Separator: Line'
#       /\p{Zp}/ - 'Separator: Paragraph'
#       /\p{C}/ - 'Other'
#       /\p{Cc}/ - 'Other: Control'
#       /\p{Cf}/ - 'Other: Format'
#       /\p{Cn}/ - 'Other: Not Assigned'
#       /\p{Co}/ - 'Other: Private Use'
#       /\p{Cs}/ - 'Other: Surrogate'

#   Lastly, \p{} matches a character's Unicode script. The following scripts are supported:

#   /\p{Arabic}/
#   /\p{Armenian}/
#   /\p{Balinese}/
#   /\p{Bengali}/
#   /\p{Bopomofo}/
#   /\p{Braille}/
#   /\p{Buginese}/
#   /\p{Buhid}/
#   /\p{Canadian_Aboriginal}/
#   /\p{Carian}/
#  /\p{Cham}/
#   /\p{Cherokee}/
#   /\p{Common}/
#   /\p{Coptic}/
#   /\p{Cuneiform}/
#   /\p{Cypriot}/
#   /\p{Cyrillic}/
#   /\p{Deseret}/
#   /\p{Devanagari}/
#   /\p{Ethiopic}/
#   /\p{Georgian}/
#   /\p{Glagolitic}/
#   /\p{Gothic}/
#   /\p{Greek}/
#   /\p{Gujarati}/
#   /\p{Gurmukhi}/
#   /\p{Han}/
#   /\p{Hangul}/
#   /\p{Hanunoo}/
#   /\p{Hebrew}/
#   /\p{Hiragana}/
#   /\p{Inherited}/
#   /\p{Kannada}/
#   /\p{Katakana}/
#   /\p{Kayah_Li}/
#   /\p{Kharoshthi}/
#   /\p{Khmer}/
#   /\p{Lao}/
#   /\p{Latin}/
#   /\p{Lepcha}/
#   /\p{Limbu}/
#   /\p{Linear_B}/
#   /\p{Lycian}/
#   /\p{Lydian}/
#   /\p{Malayalam}/
#   /\p{Mongolian}/
#   /\p{Myanmar}/
#   /\p{New_Tai_Lue}/
#   /\p{Nko}/
#   /\p{Ogham}/
#   /\p{Ol_Chiki}/
#   /\p{Old_Italic}/
#   /\p{Old_Persian}/
#   /\p{Oriya}/
#   /\p{Osmanya}/
#   /\p{Phags_Pa}/
#   /\p{Phoenician}/
#   /\p{Rejang}/
#   /\p{Runic}/
#   /\p{Saurashtra}/
#   /\p{Shavian}/
#   /\p{Sinhala}/
#   /\p{Sundanese}/
#   /\p{Syloti_Nagri}/
#   /\p{Syriac}/
#   /\p{Tagalog}/
#   /\p{Tagbanwa}/
#   /\p{Tai_Le}/
#   /\p{Tamil}/
#   /\p{Telugu}/
#   /\p{Thaana}/
#   /\p{Thai}/
#   /\p{Tibetan}/
#   /\p{Tifinagh}/
#   /\p{Ugaritic}/
#   /\p{Vai}/
#   /\p{Yi}/


# \1...\9 - Matches nth grouped subexpression.
  /([Rr])uby&\1ails/
#   Matches ruby&rails or Ruby&Rails.

# \10 - Matches nth grouped subexpression if it matched already. Otherwise refers to the octal representation of a character code.
# \& - Matches the value of an entire match.
# \` - Matches prematch subexpression.
# \' - Matches postmatch subexpression.
# \+ - Matches highest grouped subexpression.


# [...] - Matches any single character in brackets.
# [^...] - Matches any single character not in brackets
# [c1-c2] - Matches all the characters between c1 and c2, inclusive.
# [[:alnum:]] - Alphabetic and numeric character
# [[:alpha:]] - Alphabetic character
# [[:blank:]] - Space or tab
# [[:cntrl:]] - Control character
# [[:digit:]] - Digit
  # U+06F2 is "EXTENDED ARABIC-INDIC DIGIT TWO"
  /[[:digit:]]/.match("\u06F2")    #=> #<MatchData "\u{06F2}">
# [[:graph:]] - Non-blank character (excludes spaces, control characters, and similar)
# [[:lower:]] - Lowercase alphabetical character
# [[:print:]] - Like [:graph:], but includes the space character
# [[:punct:]] - Punctuation character
# [[:space:]] - Whitespace character ([:blank:], newline, carriage return, etc.)
# [[:upper:]] - Uppercase alphabetical
# [[:xdigit:]] - Digit allowed in a hexadecimal number (i.e., 0-9a-fA-F)
  /[[:upper:]][[:lower:]]/.match("Hello") #=> #<MatchData "He">
  /[[:xdigit:]][[:xdigit:]]/.match("A6")  #=> #<MatchData "A6">
# Ruby also supports the following non-POSIX character classes:
# [[:word:]] - A character in one of the following Unicode general categories Letter, Mark, Number, Connector_Punctuation
# [[:ascii:]] - A character in the ASCII character set


# regexp flags: 
       # m:  Treat a newline as a character matched by .
       # i:  Ignore case
       # x:  Ignore whitespace and comments in the pattern
       # o:  Perform #{} interpolation only once
       # u:  encoding:  UTF-8
       # e:  encoding:  EUC-JP
       # s:  encoding:  Windows-31J
       # n:  encoding:  ASCII-8BIT


re = /(\d+):(\d+)/     # match a time hh:mm
md = re.match("Time: 12:34am")
md.type   ?   MatchData
md[0]         # == $&   ?   "12:34"
md[1]         # == $1   ?   "12"
md[2]         # == $2   ?   "34"
md.pre_match  # == $`   ?   "Time: "
md.post_match # == $'   ?   "am"
# $+ contains last capture group.
# $~ is equivalent to ::last_match


Regexp.new('^\s*[a-z]')
%r{/sos/1\b}
/\brails\b/
/fg#{sos}/




# HEREDOC

if options[:usage]
  puts <<-USAGE.strip_heredoc
    This command does such and such.

    Supported options are:
      -h         This message
      ...
  USAGE
end

print <<-EOF
    This is the first way of creating
    here document ie. multiple line string.
EOF

puts(<<-EOT)
    Here goes a very long message...
    Sincerely,
    Dr. Foobear
EOT

html_escape(<<-ONE) + '<hr />' + html_escape(<<-TWO)
    Here goes my first very long message.
    Yeehaw!
ONE
    This is the second message which is still long.
    It is long indeed.
TWO

# When using heredocs in Ruby 2.3.0, use a tilde (~) instead of a minus (-)
# to remove leading whitespace while keeping indentation in the doc itself.

print <<~EOF
    This is the first way of creating
    here document ie. multiple line string.
EOF

print <<EOF
    This is the first way of creating
    here document ie. multiple line string.
EOF

print <<"EOF";                # same as above
    This is the second way of creating
    here document ie. multiple line string.
EOF

print <<`EOC`                 # execute commands
  echo hi there
  echo lo there
EOC

print <<"foo", <<"bar"  # you can stack them
  I said foo.
foo
  I said bar.
bar

string = [<<ONE, <<TWO, <<THREE]
  the first thing
ONE
  the second thing
TWO
  and the third thing
THREE

# Stacking is not acceptable without scope

<<"foo", <<"bar"  # error
  I said foo.
foo
  I said bar.
bar



# LOOPS

$i = 0
$num = 5

while $i < $num
   puts("Inside the loop i = #$i" )
   $i +=1
end

while $i < $num  do
   puts("Inside the loop i = #$i" )
   $i +=1
end

puts("Inside the loop i = #$i" ) while ($i +=1) < $num

begin
   puts("Inside the loop i = #$i" )
   $i +=1
end while $i < $num

until $i > $num
   puts("Inside the loop i = #$i" )
   $i +=1;
end

until $i > $num  do
   puts("Inside the loop i = #$i" )
   $i +=1;
end

begin
   puts("Inside the loop i = #$i" )
   $i +=1;
end until $i > $num

for i in 0..5
   puts "Value of local variable is #{i}"
end

for i, j, l in 0..5
   puts "Value of local variable is #{i}"

   retry if i == 4

   if i == 3 then
      puts "Value of local variable is #{i}"
      redo
   end

   if i < 2 then
      next
   end

   if i > 2 then
      break
   end
end

(0..5).each do |i|
   puts "Value of local variable is #{i}"
end

#Ruby 2.5 supports rescue/else/ensure inside do/end blocks.

array_from_user = [4, 2, 0, 1] => [4, 2, 0, 1]
array_from_user.each do |number|
   p 10 / number
rescue ZeroDivisionError => exception
   p exception
   next
end

# ARRAY

ary = [ "fred", 10, 3.14, "This is a string", "last element", ]
ary.each do |i|
   puts i
end

Array.new(20)
Array.new(4, "mac")



# HASH

hsh = colors = { "red" => 0xf00, "green" => 0x0f0, "blue" => 0x00f }
hsh.each do |key, value|
   print key, " is ", value, "\n"
end

H = Hash["a" => 100, "b" => 200]

TRACE VARIABLE

ruby> trace_var :$x, proc{print "$x is now ", $x, "\n"}
   nil
ruby> $x = 5
$x is now 5
   5


DEFINED

# defined? variable # True if variable is initialized

# For Example

foo = 42
defined? foo    # => "local-variable"
defined? $_     # => "global-variable"
defined? bar    # => nil (undefined)

# Usage 2

# defined? method_call # True if a method is defined

# For Example

defined? puts        # => "method"
defined? puts(bar)   # => nil (bar is not defined here)
defined? unpack      # => nil (not defined here)

# Usage 3

# True if a method exists that can be called with super user
defined? super

# For Example

defined? super     # => "super" (if it can be called)
defined? super     # => nil (if it cannot be)

# Usage 4

# defined? yield   # True if a code block has been passed

# For Example

defined? yield    # => "yield" (if there is a block passed)
defined? yield    # => nil (if there is no block)



# RANGE

(10..15).each do |n| 
   print n, ' ' 
end


(10...15).each do |n| 
   print n, ' ' 
end



# METHODS

def method_name 

end

def self.method_name 

end

def method_name(*r)

end

def method_name (var1, var2)
  return 1,2,3
end

class << self
  def lol

  end
end

def test(a1 = "Ruby", a2 = "Perl")
   puts "The programming language is #{a1}"
   puts "The programming language is #{a2}"
end

alias foo bar
alias $MATCH $&

undef bar



# BLOCK

def test
   puts "You are in the method"
   yield
   puts "You are again back to the method"
   yield
end
test {puts "You are in the block"}

def test
   yield 5
   puts "You are in the method test"
   yield 100
end
test {|i| puts "You are in the block #{i}"}

def test
   yield 5, 10, 15
end
test {|i, j, k| puts "You are in the block #{i}"}

def test(&block)
   block.call
end
test { puts "Hello World!"}

BEGIN { 
   # BEGIN block code 
   puts "BEGIN code block"
} 

END { 
   # END block code 
   puts "END code block"
}
   # MAIN block code 
puts "MAIN code block"



# EXCEPTIONS

begin  
  raise "Error Message" 
rescue OneTypeOfException, SecErrType  
# -  
rescue AnotherTypeOfException  
# -  
else
 #.. executes if there is no exception  
ensure
# Always will be executed
end



# GOTO

def promptAndGet(prompt)
   print prompt
   res = readline.chomp
   throw :quitRequested if res == "!"
   return res
end

catch :quitRequested do
   name = promptAndGet("Name: ")
   age = promptAndGet("Age: ")
   sex = promptAndGet("Sex: ")
   # ..
   # process information
end
promptAndGet("Name:")



# METHODS

def method_name

end

def Puzan.method_name

end

def self.method_name

end

def method_name(*r)

end

def method_name (var1, var2)
  return 1,2,3
end

class << self
        def lol

        end
end

class << Puzan
        def lol

        end
end

#STRUCTUTES

# In <= Ruby 2.4, structs can be created using positional arguments.

Customer = Struct.new(:name, :email)
Customer.new("John", "john@example.com")

# So in Ruby 2.5 we can create structs using keywords as long as we are passing 'keyword_init'.

Customer = Struct.new(:name, :email, keyword_init: true)
Customer.new(name: "John", email: "john@example.com")



# CLASS

class Customer

end

class << A

end

class Lol < Cool

end


o = Object.new

def o.my_method
  1 + 1
end

class << o
  def my_method
    1 + 1
  end
end


$global_variable = 10

class Customer
   VAR1 = 100
   VAR2 = 200

   @@no_of_customers = 0

   class << self   
     def bla()

     end

     def bla2

     end
   end

   def self.initialize(id, name, addr)
  o = 0
   end

   def initialize(id, name, addr)
      @cust_id = id
      @cust_name = name
      @cust_addr = addr
   end

   def display_details()
      puts "Customer id #@cust_id"
      puts "Customer name #@cust_name"
      puts "Customer address #@cust_addr"
   end

   def total_no_of_customers()
      @@no_of_customers += 1
      puts "Total number of customers: #@@no_of_customers"
   end

   def getWidth
      @width
   end
   def getHeight
      @height
   end
   # make them private
   private :getWidth, :getHeight
end

cust1 = Customer.new
cust2 = Customer. new
cust3 = Customer.new("1", "John", "Wisdom Apartments, Ludhiya")
cust2 = Customer.new("2", "Poul", "New Empire road, Khandala")

cust1.display_details()
cust1.total_no_of_customers()
cust2.display_details()
cust2.total_no_of_customers()



# MODULE

module Trig
   PI = 3.141592654
   def Trig.sin(x)
   # ..
   end
   def Trig.cos(x)
   # ..
   end
end

module A::B
  p Module.nesting #=> [A::B]
  p Z #=> raises NameError
end

y = Trig.sin(Trig::PI/4)


module Week
   FIRST_DAY = "Sunday"
   def Week.weeks_in_month
      puts "You have four weeks in a month"
   end
   def Week.weeks_in_year
      puts "You have 52 weeks in a year"
   end
end

class Decade
include Week
   no_of_yrs = 10
   def no_of_months
      puts Week::FIRST_DAY
      number = 10*12
      puts number
   end
end

# A module may be reopened any number of times to add, change or remove functionality:

module MyModule
  def my_method
  end
end

module MyModule
  alias my_alias my_method
end

module MyModule
  remove_method :my_method
end

# Reopening classes is a very powerful feature of Ruby,
# but it is best to only reopen classes you own.
# Reopening classes you do not own may lead to naming 
# conflicts or difficult to diagnose bugs.