
(setq *print-case* :capitalize)

#||
you should always use the vector function, or the more general function
make-array to create vectors you plan to modify.
||#

(setf v1 (vector 1 2 3 4 5))
(setf v2 #(a b c d e))
(setf v3 (vector 'p 'q 'r 's 't))

(write v1)
(terpri)
(write v2)
(terpri)
(write v3)
(terpri)

;; You can access the vector elements using the aref function.

(setq a (make-array 5 :fill-pointer 0))
(write a)

(vector-push 'a a)
(vector-push 'b a)
(vector-push 'c a)

(terpri)
(write a)
(terpri)

(vector-push 'd a)
(vector-push 'e a)

;this will not be entered as the vector limit is 5
(vector-push 'f a)

(write a)
(terpri)

(vector-pop a)
(vector-pop a)
(vector-pop a)

(write a)
(terpri)

(write (sort (vector "Amal" "Akbar" "Anthony") #'string<))
(terpri)

;; merging the strings
(write (merge 'vector (vector "C" "B" "F")(vector "A" "D" "E") #'string=))
(terpri)
