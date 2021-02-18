
(setq *print-case* :capitalize)

;; open filename &key :direction :element-type :if-exists :if-does-not-exist :external-format

#||
You can use the open function to create a new file or to open an existing
file. It is the most basic function for opening a file. However,
the with-open-file is usually more convenient and more commonly used,
as we will see later in this section.
||#

; (with-open-file (stream "toRead.txt"))

; read-line, read-char, delete-file, rename-file, file-length,

; :if-does-not-exist, :create, :error,

(format t "~d ~%" (type-of 5))

(let ((filep (open "toRead.txt" :if-does-not-exist nil)))
   (when filep
     (loop for line = (read-line filep nil)
       while line do (format t "~a~%" line))
     (format t "the length of the file is ~d ~%" (file-length filep))
     (close filep)))
(terpri)

(let ((filp (open "toReadInteger.txt" :if-does-not-exist nil)))
  (when filp
    (loop for number = (read filp nil)
      while number do
      (format t "type of ~d " number)
      (format t "~a ~%" (type-of number)))
    (close filp)))
(terpri)
