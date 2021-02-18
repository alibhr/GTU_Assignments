
(setq *print-case* :capitalize)

(setf myArray1 (make-array 8 :initial-contents '(0 1 2 3 4 5 6 7)))
(print myArray1)

(setf myArray2 (make-array '(8)))
(print myArray2)

(setf myArray3 (make-array '(3 3) :initial-contents '((1 2 3)(4 5 6)(7 8 9))))
(print myArray3)

(setf (aref myArray3 0 0) -1)
(print (aref myArray3 0 0))
(terpri)

;; make-array dimensions :element-type :initial-element :initial-contents :adjustable :fill-pointer  :displaced-to :displaced-index-offset

;

(setq myarray (make-array '(3 2 3)
   :initial-contents
   '(((a b c) (1 2 3))
      ((d e f) (4 5 6))
      ((g h i) (7 8 9))
   ))
)
(setq array2 (make-array '(3 2) :displaced-to myarray :displaced-index-offset 5))
(write myarray)
(terpri)
(write array2)
(terpri)

;a one dimensional array with 5 elements,
;initail value 5
(write (make-array 5 :initial-element 5))
(terpri)

;two dimensional array, with initial element a
(write (make-array '(2 3) :initial-element 'a))
(terpri)

;an array of capacity 14, but fill pointer 5, is 5
(write(length (make-array 14 :fill-pointer 5)))
(terpri)

;however its length is 14
(write (array-dimensions (make-array 14 :fill-pointer 5)))
(terpri)

; a bit array with all initial elements set to 1
(write(make-array 10 :element-type 'bit :initial-element 1))
(terpri)

; a character array with all initial elements set to a
; is a string actually
(write(make-array 10 :element-type 'character :initial-element #\a))
(terpri)

; a two dimensional array with initial values a
(setq myarray (make-array '(2 2) :initial-element 'a :adjustable t))
(write myarray)
(terpri)

;readjusting the array
(adjust-array myarray '(1 3) :initial-element 'b)
(write myarray)
