
(setq *print-case* :capitalize)

(setq *p* 7)

(if (not (or (and T T) nil))
  (print "it is true ~%")
  (print "it is false ~%"))

(if (not nil)
  (print "it is true ~%")
  (print "it is false ~%"))

#||
(if (eq *p* 7)
  (progn
    ()
    ())
  (progn
    ()
    ()))
||#

(case *p*
  (6 (print "6"))
  (7 (print "7"))
  (8 (print "8"))
  (otherwise (print "other")))
(terpri) ;; new line

(cond
  ((> *p* 7)
   (print "more than 7"))
  ((< *p* 7)
   (print "less than 7"))
  ((= *p* 7)
   (print "equal to 7")))
(terpri);; new line

(when *p* 7
  (format t "Hello from here ~%")
  (format t "end of the when ~%"))

;; /= not equal.
;; max returns the max value.
;; min returns the min value.
;; and, or, not are logical operators.

;; logand bit-wise logical and operator
;; logior bit-wise logical or operator
;; logxor bit-wise logical exclusive or operator
;; lognor bit-wise logical not
;; logeqv bit-wise logical EQUIVALENCE (also known as exclusive nor)
