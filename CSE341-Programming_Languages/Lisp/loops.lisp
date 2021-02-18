
(setq *print-case* :capitalize)

(loop for i from 0 to 3 do
  (format t "~d " i))
(terpri);; new line
;
(print(loop for i upto 10 collect i))
(terpri)
;
(loop for i from 11 downto 0 do
  (format t "~d " i))
(terpri);; new line

(setq i 0)
(loop
  (if (>= i 10)(return i))
  (format t "~d " i)
  (setq i (+ i 1)))
(terpri);; new line

(loop for x in '(peter paul mary) do
  (format t "~s " x))
(terpri);; new line

(dotimes (y 12)
         (format t "~s " y))
(terpri);; new line

(do ((x 0 (+ 2 x))(y 20 ( - y 2)))
   ((= x y)(- x y))
   (format t "x = ~d  y = ~d~%" x y))
;
(write (loop for i in '(bird 3 4 turtle (1 . 4) horse cat)
            when (symbolp i) collect i))
(terpri);; new line

;(loop for c across "bacon" do (princ c))

;(map nil #'princ "bacon")
