(load "gpp_lexer.lisp")

(defvar varList (list))
(defvar varValues (list))

(defun gppinterpreter()
  (let ((line nil))
    (cond
      ((= (length *args*) 0)
        (with-open-file (ostream "interpreter_output.txt" :direction :output)
          (setf line (read-line))
          (loop while(string/= line "")
            do
            (setq tokens (list))
            (setq splited-line (list))

            ;; lexer works here
            (evaluate-a-line line)
            (setq tokens (reverse tokens))
            (setq splited-line (reverse splited-line))

            (if (not (equal (car tokens) "COMMENT" ))
              (progn
                (setq result (INPUT))
                (if (equal (cadr result) -1)
                  (progn
                    (format t "SYNTAX_ERROR Expression not recognized ~%")
                    (format ostream "SYNTAX_ERROR Expression not recognized ~%"))
                  (progn
                    (setq result (car result))
                    (format t "Syntax OK.~%")
                    (format t "Result: ~d ~%" result)
                    (format ostream "Syntax OK.~%")
                    (format ostream "Result: ~d~%" result))))
              (progn
                (format t "Syntax OK.~%")
                (format t "Result: COMMENT ~%")
                (format ostream "Syntax OK.~%")
                (format ostream "Result: COMMENT ~%")))
            (terpri)
            (setf line (read-line)))))

      ((= (length *args*) 1)
        (prog ()
          (with-open-file (ostream "interpreter_output.txt" :direction :output)
            (with-open-file (istream (car *args*) :if-does-not-exist nil :direction :input)
              (if (eql istream nil) (return (format t "~%File does not exist.~%")))
                (setf line (read-line istream nil))
              (loop while(not(eql line nil))
                do
                (setq tokens (list))
                (setq splited-line (list))
                (if (string/= line "") (evaluate-a-line line))
                (setq tokens (reverse tokens))
                (setq splited-line (reverse splited-line))
                (if (not (equal (car tokens) "COMMENT" ))
                  (progn
                    (setq result (INPUT))
                    (if (equal (cadr result) -1)
                      (progn
                        (format t "SYNTAX_ERROR Expression not recognized ~%")
                        (format ostream "SYNTAX_ERROR Expression not recognized ~%"))
                      (progn
                        (setq result (car result))
                        (format t "Syntax OK.~%" )
                        (format t "Result: ~d ~%" result)

                        (format ostream "Syntax OK.~%")
                        (format ostream "Result: ~d~%" result))))
                  (progn
                    (format t "Syntax OK.~%")
                    (format t "Result: COMMENT ~%")
                    (format ostream "Syntax OK.~%")
                    (format ostream "Result: COMMENT ~%")))
                (terpri)
                (format t "~%")
                (setf line (read-line istream nil)))))))
      (t (format t "~%Too many arguments given as parameters.~%")))))

(defun EXPI(ExpTo ExpS)
  (prog ( (len (list-length ExpTo)) )
    (cond
      ((and (= len 1) (string= (car ExpTo) "VALUE")) (return (parse-integer (car ExpS))))
      ((and (= len 1) (string= (car ExpTo) "IDENTIFIER")) (return (nth (varValue (car ExpS)) varValues)))

      ;; +
      ((and (> len 4) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "OP_PLUS"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPI nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPI (subseq nExpTo lIndex))))

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPI lExp lExpS))
              (setq RO (EXPI rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO nil)) )
                (return-from EXPI (+ LO RO) )
                (return-from EXPI nil)))
            (return-from EXPI nil))))

      ;; -
      ((and (> len 4) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "OP_MINUS"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))
          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPI nExpTo))
          (if (/= lIndex 0) (setq rIndex (divideEXPI  (subseq nExpTo lIndex))))
          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPI lExp lExpS))
              (setq RO (EXPI rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO nil)))
                (return-from EXPI (- LO RO) )
                (return-from EXPI nil)))

            (return-from EXPI nil))))

      ;; *
      ((and (> len 4) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "OP_MULT"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPI nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPI (subseq nExpTo lIndex))))

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPI lExp lExpS))
              (setq RO (EXPI rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO nil)))
                (return-from EXPI (* LO RO) )
                (return-from EXPI nil)))

            (return-from EXPI nil))))

      ;; /
      ((and (> len 4) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "OP_DIV"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPI nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPI (subseq nExpTo lIndex))))

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPI lExp lExpS))
              (setq RO (EXPI rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO nil)))
                (return-from EXPI (/ LO RO) )
                (return-from EXPI nil)))

            (return-from EXPI nil))))

      ;; set
      ((and (> len 4) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_SET"))
        (let ((LO) (index) (lExp) (lExpS))

          (if (string= (third ExpTo) "IDENTIFIER")
            (progn
              (setq index (varValue (third ExpS)))
              (setq lExp (subseq ExpTo 3 (- len 1)))
              (setq lExpS (subseq ExpS 3 (- len 1)))
              (setq LO (EXPI lExp lExpS))

              (if (not (eql LO nil))
                (return-from EXPI (setf (nth index varValues) LO) )
                (return-from EXPI nil)))

            (return-from EXPI nil))))

      ;; if EXB EXPI
      ((and (> len 4) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_IF"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPB nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPI (subseq nExpTo lIndex))))

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPB lExp lExpS))
              (setq RO (EXPI rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO nil)))
                (if (= LO 1)
                  (return-from EXPI RO)
                  (return-from EXPI 0))
                (return-from EXPI nil)))

            (return-from EXPI nil))))

      (t (return-from EXPI nil)))))

(defun EXPB(ExpTo ExpS)
  (prog ( (len (list-length ExpTo)) (BV) )
    (cond
      ;; Binary Value
      ( (and (= len 1) (string= (car ExpTo) "VALUE"))
        (if (or (eql 0 (setq BV (parse-integer (car ExpS)))) (eql 1 BV) )
          (return BV)
          (return nil)))

      ;; true
      ( (and (= len 1) (string= (car ExpTo) "KW_TRUE"))
        (return 1))

      ;; false
      ( (and (= len 1) (string= (car ExpTo) "KW_FALSE"))
        (return 0))

      ;; and
      ((and (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_AND"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))
          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPB nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPB (subseq nExpTo lIndex))))

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPB lExp lExpS))
              (setq RO (EXPB rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO nil)))
                (return-from EXPB (if (and (= LO 1) (= RO 1)) 1 0) )
                (return-from EXPB nil)))

            (return-from EXPB nil))))

      ;; or
      ((and (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_OR"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))
          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPB nExpTo))
          (if (/= lIndex 0) (setq rIndex (divideEXPB (subseq nExpTo lIndex))))
          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPB lExp lExpS))
              (setq RO (EXPB rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO nil)))
                (return-from EXPB (if (or (= LO 1) (= RO 1)) 1 0))
                (return-from EXPB nil)))

            (return-from EXPB nil))))

      ;; Keyword equal
      ((and (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_EQUAL"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPB nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPB (subseq nExpTo lIndex))))

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPB lExp lExpS))
              (setq RO (EXPB rExp rExpS))
              (if (and (eql LO nil) (eql RO nil))
                (progn
                  (setq lIndex (divideEXPI nExpTo))

                  (if (/= lIndex 0) (setq rIndex (divideEXPI (subseq nExpTo lIndex))))

                  (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
                    (progn
                      (setq lExp (subseq nExpTo 0 lIndex))
                      (setq rExp (subseq nExpTo lIndex))

                      (setq lExpS (subseq nExpS  0 lIndex))
                      (setq rExpS (subseq nExpS lIndex))

                      (setq LO (EXPI lExp lExpS))
                      (setq RO (EXPI rExp rExpS)))
                    (return-from EXPB nil))))

              (if (and (not (eql LO nil)) (not (eql RO nil)))
                (return-from EXPB (if (= LO RO) 1 0) )
                (return-from EXPB nil)))

            (return-from EXPB nil))))

      ;; Keyword not
      ((and (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_NOT"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPB nExpTo))

          (if (and (/= lIndex 0) (= (+ 3 lIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq lExpS (subseq nExpS  0 lIndex))
              (setq LO (EXPB lExp lExpS))

              (if (not (eql LO nil))
                (return-from EXPB (if (= LO 1) 0 1) )
                (return-from EXPB nil)))

            (return-from EXPB nil))))

      (t (return-from EXPB nil)))))

(defun EXPLISTI(ExpTo ExpS)
  (prog ((len (list-length ExpTo)) (tempList))
    (cond
      ;; null
      ((and (= len 1) (string= (first ExpTo) "KW_NIL"))

        (return nil))
      ;; list value
      ((not (equal (setq tempList (LISTVALUE ExpTo ExpS)) -1))

        (return tempList))

      ;; append
      ((and (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_APPEND"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPI nExpTo))

          (if (and (/= lIndex 0))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPI lExp lExpS))
              (setq RO (EXPLISTI rExp rExpS))

              (if (and (not (eql LO nil)) (not (equal RO -1)))
                (return-from EXPLISTI (cons LO RO) )
                (return-from EXPLISTI -1)))

            (return-from EXPLISTI -1))))

      ;; concat
      ((and (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_CONCAT"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPLISTI nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPLISTI (subseq nExpTo lIndex))) )

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPLISTI lExp lExpS))
              (setq RO (EXPLISTI rExp rExpS))

              (if (and (not (eql LO -1)) (not (eql RO -1)))
                (return-from EXPLISTI (append LO RO) )
                (return-from EXPLISTI -1)))

            (return-from EXPLISTI -1))))

      ;; if EXB EXPLISTI
      ((and (> len 4) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_IF"))
        (let ((LO) (RO) (lIndex) (rIndex) (lExp) (rExp) (nExpTo)  (nExpS) (lExpS) (rExpS))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))
          (setq lIndex (divideEXPB nExpTo))

          (if (/= lIndex 0) (setq rIndex (divideEXPLISTI (subseq nExpTo lIndex))))

          (if (and (/= lIndex 0) (/= rIndex 0) (= (+ 3 lIndex rIndex) len))
            (progn
              (setq lExp (subseq nExpTo 0 lIndex))
              (setq rExp (subseq nExpTo lIndex))

              (setq lExpS (subseq nExpS  0 lIndex))
              (setq rExpS (subseq nExpS lIndex))

              (setq LO (EXPB lExp lExpS))
              (setq RO (EXPLISTI rExp rExpS))

              (if (and (not (eql LO nil)) (not (eql RO -1)))
                (if (= LO 1)
                  (return-from EXPLISTI RO)
                  (return-from EXPLISTI 0))
                (return-from EXPLISTI -1)))

            (return-from EXPLISTI -1))))

      (t (return-from EXPLISTI -1)))))

(defun LISTVALUE(ExpTo ExpS)
  (let ( (len (list-length ExpTo)) )
    (cond
      ;; null
      ((and (= len 1) (string= (first ExpTo) "KW_NIL"))

        (return nil))

      ((and (= len 3) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_LIST"))

        (return nil))

      ;; and
      ((and (> len 3) (string= (first ExpTo) "OP_OP") (string= (car (last ExpTo)) "OP_CP") (string= (second ExpTo) "KW_LIST"))
        (let ((index 0) (nExpTo) (nExpS) (tempList))

          (setq nExpTo (subseq ExpTo 2 (- len 1)))
          (setq nExpS (subseq ExpS 2 (- len 1)))

          (loop for temp in nExpTo
              do
                (if (string= temp "VALUE")
                  (push (parse-integer (nth index nExpS)) tempList)
                  (return-from LISTVALUE -1))
                (setf index (+ index 1)))
          (return-from LISTVALUE (reverse tempList))))
      (t (return-from LISTVALUE -1)))))

(defun varValue(ID)
  (let ((index 0))
    (loop for temp in varList
        do
          (if (string= temp ID) (return-from varValue index))

          (setf index (+ 1 index)))
    (push ID varList)
    (push -1 varValues)
    (return 0)))

(defun divideEXPI(ExpTo)
  (let ((index 0) (PC 0))
    (cond
      ((or (string= (car ExpTo) "VALUE") (string= (car ExpTo) "IDENTIFIER")) (return-from divideEXPI 1 ))

      ((string= (car ExpTo) "OP_OP")
        (progn
          (loop for temp in ExpTo
              do
                (setf index (+ index 1))
                (if (string= temp "OP_OP") (setf PC (+ PC 1)))
                (if (string= temp "OP_CP") (setf PC (- PC 1)))
                (if (= PC 0) (return-from divideEXPI index)))
          (return-from divideEXPI 0)))
      ( t (return-from divideEXPI 0)))))

(defun divideEXPB(ExpTo)
  (let ((index 0) (PC 0))
    (cond
      ((or (string= (car ExpTo) "VALUE") (string= (car ExpTo) "KW_TRUE") (string= (car ExpTo) "KW_FALSE")) (return-from divideEXPB 1 ))

      ((string= (car ExpTo) "OP_OP")
        (progn
          (loop for temp in ExpTo
              do
                (setf index (+ index 1))
                (if (string= temp "OP_OP") (setf PC (+ PC 1)))
                (if (string= temp "OP_CP") (setf PC (- PC 1)))
                (if (= PC 0) (return-from divideEXPB index)))
          (return-from divideEXPB 0)))
      ( t (return-from divideEXPB 0)))))

(defun divideEXPLISTI(ExpTo)
  (let ((index 0) (PC 0))
    (cond
      ((string= (car ExpTo) "KW_NIL") (return-from divideEXPLISTI 1 ))

      ((string= (car ExpTo) "OP_OP")
        (progn
          (loop for temp in ExpTo
              do
                (setf index (+ index 1))
                (if (string= temp "OP_OP") (setf PC (+ PC 1)))
                (if (string= temp "OP_CP") (setf PC (- PC 1)))
                (if (= PC 0) (return-from divideEXPLISTI index)))
          (return-from divideEXPLISTI 0)))
      ( t (return-from divideEXPLISTI 0)))))

(defun INPUT ()
  (prog (value)
    (if (eql (setq value (EXPI tokens splited-line)) nil)

      (if (not (eql (setq value (EXPLISTI tokens splited-line)) -1))
        (return (list value 1))

        (return (list value -1)))
      (return (list value 1)))))


(gppinterpreter)
