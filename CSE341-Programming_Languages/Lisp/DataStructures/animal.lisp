
(setq *print-case* :capitalize)

(defclass animal()
  (name
   sound))

(setf dog (make-instance 'animal))

(setf (slot-value dog 'name) "spot")
(setf (slot-value dog 'sound) "woof")

(format t "~a says ~a ~%"
        (slot-value dog 'name)
        (slot-value dog 'sound))

(defclass mammal()
  ((name
    :initarg :name
    :initform (error "Must provide a name"))
   (sound
    :initarg :sound
    :initform "No sound"
    :accessor mammal-sound))) ;; getter, setter automatically.(reader(getter), writer(setter))

(defvar *cat* (make-instance 'mammal :name "cat" :sound "meow"))

(defgeneric make-sound (mammal))
(defmethod make-sound ((the-mammal mammal))
  (format t "~a says ~a ~%"
          (slot-value the-mammal 'name)
          (slot-value the-mammal 'sound)))

(make-sound *cat*)

(defgeneric (setf mammal-name)(value the-mammal))
(defmethod (setf mammal-name)(value (the-mammal mammal))
  (setf (slot-value the-mammal 'name) value))

(setf (mammal-name *cat*) "haydar")
(setf (mammal-sound *cat*) "meoow")
(make-sound *cat*)

(defclass dog(mammal)())
