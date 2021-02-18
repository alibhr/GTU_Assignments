
(defvar *srcFileName* "nested_list.txt")
(defvar *destFileName* "flattened_list.txt")

(defun flattener-write (file llines)
  ""
  (dolist (lline llines)
          (if (listp lline)
            (flattener-write file lline)
            (format file "~d " lline))))

(defun flattener-collect (llines)
  ""
  (let((localList))
    (dolist (lline llines)
            (if (not(listp lline))
              (setf localList (append localList (list lline)))
              (setf localList (append localList (flattener-collect lline)))))
    localList))

(defun flattener-read(filePathSrc filePathDst)
  ""
  (let ((filep (open filePathSrc :if-does-not-exist nil))(lline))
    (when filep
      (with-open-file (out filePathDst :direction :output :if-exists :supersede)
        (loop for line = (read-line filep nil)
          while line do
          (setf lline (read-from-string (concatenate 'string "(" line ")")))
          (format out "~a" (flattener-collect lline))
          (format out "~%"))
        (close out)
        (close filep))
     T)))


(flattener-read *srcFileName* *destFileName*)
