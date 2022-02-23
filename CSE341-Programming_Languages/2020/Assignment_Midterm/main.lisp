(defun main ()
	(let ((parsed_list)(queries)(facts)(predicates)(results))
		(setf parsed_list (read-file "input.txt"))
		(dolist (element parsed_list)
			(cond
				((is-query element)
					(setf queries (append queries (list element))))
				((is-fact element )
					(setf facts (append facts (list element))))
				((is-predicate element)
					(setf predicates (append predicates (list element))))))

		;(format t "queries: ")
		;(print-liste queries)
		;(format t "facts: ")
		;(print-liste facts)
		;(format t "predicates: ")
		;(print-liste predicates)

		(dolist (query queries)
			(setf results (append results (list (make-query query facts predicates)))))

		;(format t "results: ")
		;(print-liste results)

		T))

(defun read-file (srcFileName)
	(let ((filep (open srcFileName :if-does-not-exist nil)))
		(read filep nil)))

(defun is-query (element) 
	(null (car element)))

(defun is-fact (element)
	(null (cadr element)))

(defun is-predicate (element)
	(and
		(not (null (car element))) 
		(not (null (cadr element)))))

(defun print-liste (liste) 
	(dolist (e liste) 
		(format t "~a~%" e)))

(defun make-query (query facts predicates)
	(check-fact query facts))

(defun check-fact (query facts)
	(dolist (fact facts)
		(format t "~a | ~a | ~a | ~a | ~a | ~a ~%" query fact (caadr query) (caaar facts) (length(cadadr query)) (length(cadar fact)))
		(when (and 
			(string= (caadr query) (caaar facts))
			(= (length(cadadr query)) (length(cadar fact))))
				(form t "HERE0"))))

(defun is-equal-liste (l1 l2) 
	(cond
		((and(null l1)(null l2))(return-from is-equal-liste T))
		((or (null l1)(null l2))(return-from is-equal-liste nil))
		((and(stringp l1)(stringp l2))(return-from is-equal-liste (string= l1 l2)))
		((and(integerp l1)(integerp l2))(return-from is-equal-liste (= l1 l2)))
		((and(listp l1)(listp l2))(and
			(is-equal-liste (car l1) (car l2))
			(is-equal-liste (cdr l1) (cdr l2))))))

;;
(main)

(format t "~a~%" (is-equal-liste '(1 2 "ali" ("bahar" 1)) '(1 2 "ali" ("bahar" 1)) ))
