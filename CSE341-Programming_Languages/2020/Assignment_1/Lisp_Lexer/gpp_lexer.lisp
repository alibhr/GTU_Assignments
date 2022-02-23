
(defvar is-open nil)

(defun gppinterpreter (&optional file-name)
  (with-open-file (out "parsed_lisp.txt" :direction :output :if-exists :supersede)
    (if (not (null file-name))
      (interpreter-from-file file-name out)
      (interpreter-from-terminal out))
    (close out)))

(defun interpreter-from-file (file-name output-file)
  (let((filep (open file-name :if-does-not-exist nil)))
    (if filep
      (loop for line = (read-line filep nil)
        while line do
        (evaluate-a-line (format nil "~a~% " line) output-file)))))

(defun interpreter-from-terminal (output-file)
  (let((line "not-empty"))
    (loop
      (setf line (read-line))
      (if (string= line "")
        (return T)
        (evaluate-a-line (format nil "~a~% " line) output-file)))))

(defun evaluate-a-line (line output-file)
  (let((the-liste nil)(the-key nil))
    (setf the-liste (line-to-liste line))
    (loop for element in the-liste do
      (setf the-key (get-key element))
      (format output-file "~a~%" the-key)
      (format t "~a~%" the-key))))

(defun line-to-liste (line)
  (let((the-lst nil)(temp-lst nil)(str-form nil))
    (loop for chr across line do
      (if (is-a-border chr)
        (progn
         (when (not(null temp-lst))
          (setf str-form (liste-to-string temp-lst))
          (setf the-lst (append the-lst (list str-form)))
          (when (string= str-form ";;")
            (return-from line-to-liste the-lst))
          (when (is-visible chr)
            (setf the-lst (append the-lst (list (format nil "~a" chr))))))
         (when (and (is-visible chr)(null temp-lst))
           (setf the-lst (append the-lst (list (format nil "~a" chr)))))
         (setf temp-lst nil))
        (setf temp-lst (append temp-lst (list chr)))))
    the-lst))

(defun liste-to-string (lst)
  (format nil "~{~A~}" lst))

(defun is-visible (chr)
  (or (= (char-code chr) 34)
      (= (char-code chr) 40)
      (= (char-code chr) 41)))

(defun is-a-border (chr)
  (or
   (and
    (>= (char-code chr) 9)
    (<= (char-code chr) 13))
   (= (char-code chr) -1)
   (= (char-code chr) 32)
   (is-visible chr)))

(defun get-key (str)
  (let ((key nil))
    (setf key (get-key-helper str (get-keyword-liste)))
    (if (not(null key))
      (return-from get-key key))
    (setf key (get-key-helper str (get-operator-liste)))
    ;; TODO:
    (when (or(string= key "OP_OC")(string= key "OP_CC"))
      (if is-open (setf key "OP_CC")(setf key "OP_OC"))
      (if is-open (setf is-open nil)(setf is-open t))
      (return-from get-key key))
    (if (not(null key))
      (return-from get-key key))
    (setf key (get-value-identifier str))
    (if (not(null key))
      (return-from get-key key))))

(defun get-key-helper (str key-liste)
  (loop for key in key-liste do
    (if(string= (car key) str)
      (return-from get-key-helper (cadr key))))
  (return-from get-key-helper nil))

(defun get-keyword-liste ()
  '( ("and" "KW_AND")("or" "KW_OR")("not"  "KW_NOT")("equal" "KW_EQUAL")
     ("less" "KW_LESS")("nil" "KW_NIL")("list" "KW_LIST")("append" "KW_APPEND")
     ("concat" "KW_CONCAT")("set" "KW_SET")("deffun" "KW_DEFFUN")("for" "KW_FOR")
     ("if" "KW_IF")("exit" "KW_EXIT")("load" "KW_LOAD")("disp" "KW_DISP")
     ("true" "KW_TRUE")("false" "KW_FALSE")))

(defun get-operator-liste ()
  '(("+" "OP_PLUS")("-" "OP_MINUS")("/" "OP_DIV")
    ("*" "OP_MULT")("(" "OP_OP")(")" "OP_CP")
    ("**" "OP_DBLMULT")("\"" "OP_OC")("\"" "OP_CC")
    ("," "OP_COMMA")(";;" "COMMENT")))

(defun get-value-identifier (str)
  (when (is-digit (char str 0))
    (if (and (is-zero (char str 0))(/= (length str) 1))
      (return-from get-value-identifier
                   (format nil "SYNTAX_ERROR ~a cannot be tokenized" str)))
    (loop for chr across str do
      (if(not(is-digit chr))
        (return-from get-value-identifier
                     (format nil "SYNTAX_ERROR ~a cannot be tokenized" str))))
    (return-from get-value-identifier "VALUE"))

  (loop for chr across str do
    (if (not(is-alnum chr))
      (return-from get-value-identifier
                   (format nil "SYNTAX_ERROR ~a cannot be tokenized" str))))
  (return-from get-value-identifier "IDENTIFIER"))

(defun is-alnum (chr)
  (or(is-digit chr)(is-alphabetical chr)))

(defun is-digit (chr)
  (is-among chr #\0 #\9))

(defun is-zero (chr)
  (= (char-code chr) 48))

(defun is-alphabetical (chr)
  (or(is-uppercase chr)(is-lowercase chr)))

(defun is-uppercase (chr)
  (is-among chr #\A #\Z))

(defun is-lowercase (chr)
  (is-among chr #\a #\z))

(defun is-among (chr lowerbound upperbound)
  (if(characterp chr)
   (and
    (>= (char-code chr) (char-code lowerbound))
    (<= (char-code chr) (char-code upperbound)))
   nil))
;;

;;
(gppinterpreter (car *args*))
