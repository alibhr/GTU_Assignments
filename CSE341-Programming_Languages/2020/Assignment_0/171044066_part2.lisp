
(defvar *srcFileName* "boundries.txt")
(defvar *destFileName* "primedistribution.txt")

(defun is-prime (num)
  ""
  (when (<= num 2)(return-from is-prime nil))
  (let((counter 0))
    (loop for i from 2 to (/ num 2) do
      (when (= 0 (mod num i))
        (setf counter (+ counter 1))))
    (= counter 0)))

(defun is-semi-prime (num)
  (let((i 2)(counter 0))
    (loop (if (or(>= counter 2)(>(* i i) num))(return -1))
      (loop (if (/= (mod num i) 0)(return -1))
        (setf num (/ num i))
        (incf counter))
      (incf i))
    (if (> num 1)(incf counter))
    (= counter 2)))

(defun readTwoInteger(fileName)
  ""
  (let ((filep (open fileName :if-does-not-exist nil))(i 0)(nums (make-array 2))(lline))
    (when filep
      (loop for line = (read-line filep nil)
        while line do
        (setf lline (read-from-string (concatenate 'string "(" line ")")))
        (dolist (e lline)
                (when (integerp e)
                  (when (> i 1)(return))
                  (setf (aref nums i) e)
                  (setf i (+ i 1)))))
      (close filep))
    nums))

(defun primecrawler(srcFileName destFileName)
  ""
  (let(( nums (readTwoInteger srcFileName)))
    (with-open-file (out destFileName :direction :output :if-exists :supersede)
      (loop for i from(aref nums 0) to (aref nums 1)do
      	(if (is-semi-prime i)(format out "~d is Semi-prime ~%" i))
      	(if (is-prime i)(format out "~d is Prime ~%" i)))
      (close out))))


(primecrawler *srcFileName* *destFileName*)
