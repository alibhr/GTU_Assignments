
(setq *print-case* :capitalize)

(defconstant PI 3.141592)

(defun factorial (n)
  ""
  (if (= n 1)
    1
    (* n (factorial(- n 1)))))

(defun hello-you (name)
  "says hello to specified person"
  (format t "Hello ~a! ~%" name)
  (format t "this is new line ~% ~%"))

(defun isPrime(n iter)
  ""
  (if (< (/ n 2) iter) 1
    (if (= 0 (mod n iter)) 0
      (isPrime n (+ iter 1)))))

(defun readAndPrint()
  ""
  (defvar sth (read))
  (format t "~d" sth)
  (setf sth "q")
  sth)

(defun print-list(w x &optional y z)
  (format t "List = ~a ~%" (list w x y z)))

(defun sum (&rest nums)
  (setf sum 0)
  (dolist (num nums)
          (setf sum (+ sum num)))
  sum)

(defun print-list1(w &optional x &key y z)
  (format t "List = ~a ~%" (list w x y z)))

(defun difference(n1 n2)
  (return-from difference (- n1 n2)))

(defun squares (num)
  (values (expt num 2)(expt num 3)))

(defun times-3 (x)(* 3 x))
(defun times-4 (x)(* 4 x))
(defun multiples (mult-function max-num)
  (dotimes (i max-num)
           (format t "(~d : ~d )" i (funcall mult-function i))))

(defun rValue(val)
  (setq i 5)
  (return-from rValue (* val i)))

;;(print(readAndPrint))

(format t "~a factorial : ~a ~%" 5 (factorial 5))
(defvar *p* 101)
(format t "is prime (~3@a) : ~3a ~%" *p* (isPrime *p* 2))
(setf *p* 10)
(format t "is prime (~3@a) : ~3a ~%" *p* (isPrime *p* 2))
(setf *p* 7)
(format t "is prime (~3@a) : ~3a ~%" *p* (isPrime *p* 2))

(format t "~d ~%" (rem 101 3))
(format t "~,3f ~%" (log 101 3))
(format t "~d ~%" (eq 'dog 'dog))
(format t "~d ~%" (eq 'dog 'dogi))
(format t "~d ~%" (null nil))
;;floor, ceiling, max, min, oddp, evenp, numberp, sin, cos, tan, asin, atan.

(format t "(equalp 1 1.0) : ~d ~%" (equalp 1 1.0))
(format t "(equal 1 1.0) : ~d ~%" (equal 1 1.0))
(format t "(equalp \"ALI\" \"ali\") : ~d ~%" (equalp "ALI" "ali"))
(format t "(equal \"ALI\" \"ali\") : ~d ~%" (equal "ALI" "ali"))

(print-list 1 2 3)

(format t "sum function : ~d ~%" (sum 1 2 3 4 5 6 7))

(print-list1 1 2 :y 3)

(format t "difference : ~d ~%" (difference 10 2))

(format t "A number ~a ~%" (mapcar #'numberp '(2 3 4 T nil)))

(multiple-value-bind (a b) (squares 2)(format t "2^2 : ~a, 2^3 : ~a ~%" a b))

(multiples #'times-3 8)
(terpri);; new line

(mapcar (lambda(n)(format t "~a " (* n 3))) '(1 2 3))
(terpri);; new line

(print (rValue 3))

#||

sin, cos, tan, acos, asin, atan : Respective trigonometric functions.
sinh, cosh, tanh, acosh, asinh, atanh : Respective hyperbolic functions.
exp : Exponentiation function. Calculates ex
expt : Exponentiation function, takes base and power both.
sqrt : It calculates the square root of a number.
log : Logarithmic function. It one parameter is given, then it calculates its natural logarithm, otherwise the second parameter is used as base.
conjugate : It calculates the complex conjugate of a number. In case of a real number, it returns the number itself.
abs : It returns the absolute value (or magnitude) of a number.
gcd : It calculates the greatest common divisor of the given numbers.
lcm : It calculates the least common multiple of the given numbers.
isqrt : It gives the greatest integer less than or equal to the exact square root of a given natural number.
floor, ceiling, truncate, round :
ffloor, fceiling, ftruncate, fround :
mod, rem : Returns the remainder in a division operation.
float : Converts a real number to a floating point number.
rational, rationalize : Converts a real number to rational number.
numerator, denominator : Returns the respective parts of a rational number.
realpart, imagpart : Returns the real and imaginary part of a complex number.

||#
