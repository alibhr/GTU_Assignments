
(defvar *srcFileName* "integer_inputs.txt")
(defvar *destFileName* "collatz_outputs.txt")

(defun readInteger-atMost(fileName bound)
  ""
  (let ((filep (open fileName :if-does-not-exist nil))(i 0)(myList (make-list bound))(lline))
    (when filep
      (loop for line = (read-line filep nil)
        while line do
        (setf lline (read-from-string (concatenate 'string "(" line ")")))
        (dolist (e lline)
                (when (and (integerp e)  (< i bound))
                  (setf (elt myList i) e)
                  (setf i (+ i 1))))))
    (close filep)
    myList))

(defun collatz-sequence(num file)
  ""
  (loop
    (format file "~d " num)
    (if (<= num 1)(return num))
    (if (= 0 (mod num 2))
      (setf num (/ num 2))
      (setf num (+ 1 (* 3 num)))))
  (format file "~%"))

(defun collatz-sequences(srcFileName destFileName)
  ""
  (let ((numbers (readInteger-atMost srcFileName 5)))
    (with-open-file (out destFileName :direction :output :if-exists :supersede)
      (loop for num in numbers do
        (when (not(null num))
          (format out "~d: " num)
          (collatz-sequence num out)))
      (close out))))


(collatz-sequences *srcFileName* *destFileName*)
