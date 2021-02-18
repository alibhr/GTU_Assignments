
#||

  multiline comment

||#

(defun hello-you (name)
  "says hello to specified person"
  (format t "Hello ~a! ~%" name)
  (format t "this is new line ~% ~%"))

(setq *print-case* :capitalize)

(defvar *name* (read))
(hello-you *name*)

(defvar *p* 101)
(print (type-of *p*))

(format t "~a ~%" *args*)
(format t "~a ~%" (length *args*))

;; car=first element, cdr=everything else, cadr=2nd element.
;; lispt = is it a list ?
;; member = does it contain specific value inside the list.
;; push, append
;; nth
;; assoc

;;local variables( local variables can also be created using the setq construct.)
(let ((a "a")(b "b"))(print a)(print b))
(prog ((n1 '(1 2 3))(n2 '(4 5 6)))(print n1)(print n2))

(setq mi 0)
(incf mi 1)
(print mi)
(incf mi 2)
(print mi)
(decf mi 3)
(print mi)
(terpri)

(format t "~a ~%" (read-line))
