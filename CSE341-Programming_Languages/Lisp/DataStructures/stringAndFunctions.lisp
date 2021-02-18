
(setq *print-case* :capitalize)

(write-line "\"Hello\", are you there !")

;; case sensitive comparison:
;; string=, string/=, string<, string>, string<=, string>=

;; case insensitive comparison:
;; string-equal, string-not-equal, string-lessp, string-greaterp,
;;   string-not-greaterp, string-not-lessp

;; string-upcase : Converts the string to upper case
;; string-downcase : Converts the string to lower case
;; string-capitalize : Capitalizes each word in the string

#||
string-trim : It takes a string of character(s) as first argument and a string
as the second argument and returns a substring where all characters that
are in the first argument are removed off the argument string.
||#

;; String-left-trim
;; String-right-trim
;; length
;; The reverse function reverses a string.

#||
The subseq function returns a sub-string (as a string is also a sequence)
starting at a particular index and continuing to a particular ending
index or the end of the string.
||#

;; The char function allows accessing individual characters of a string.
;; sorting the strings

(write-line (concatenate 'string "Are we not drawn onward, " "we few, drawn onward to new era "))
