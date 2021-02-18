
(defvar *srcFileName* "paragraph.txt")
(defvar *destFileName* "huffman_codes.txt")

(defun calculate-frequency (fileName)
  "returns the frequencies of the characters in the given file"
  (let (
        (freqTable (make-hash-table :size 43 :rehash-size 3 :rehash-threshold 0.8 :initial-contents 0))
        (filep (open fileName :if-does-not-exist nil)))
    (when filep
      (loop for chr = (read-char filep nil)
        while chr do
        (incf (gethash chr freqtable 0) 1))
      (close filep))
    freqtable))

(defun non-null-length (arr)
  "returns the length except nil cells"
  (let ((l 0)(lOfArr (length arr)))
    (loop for i from 0 to (- lOfArr 1) do
      (when (not(null(aref arr i)))
        (setf l (+ l 1))))
    (return-from non-null-length l)))

;; the parameter must be an array and it must have list elements
;; and the first element of the list is considered for comparison operations
;; example element of array : (frequency character left-of-tree right-of-tree)
;; every element is considered as node of the tree
(defun get-smallest-element (arr)
  "returns the index of the node which has the minimum frequency."
  (let ((minElement (aref arr 0))(minIndex 0))
    (loop (if(or (not(null minElement))(>= minIndex (length arr)))(return minIndex))
      (incf minIndex)
      (setf minElement (aref arr minIndex)))

    (loop for i from 0 to (- (length arr) 1) do
      (when (and(not(null (aref arr i))) (< (car(aref arr i)) (car minElement)))
        (setf minIndex i)
        (setf minElement (aref arr i))))
    (return-from get-smallest-element minIndex)))

(defun create-arr-from-table (table)
  ""
  (let((arr (make-array (hash-table-size table)))(i 0))
    (loop for k being the hash-keys in freqTable using (hash-value v) do
      (setf (aref arr i) (list v k nil nil))
      (incf i))
    (return-from create-arr-from-table arr)))

(defun create-huffman-tree (freqArray)
  (let((first nil)(second nil)(newest nil)(index 0))
    (loop (if (<= (non-null-length freqArray) 1)(return nil))
      (setf index (get-smallest-element freqArray))
      (setf first (aref freqArray index))
      (setf (aref freqArray index) nil)

      (setf index (get-smallest-element freqArray))
      (setf second (aref freqArray index))
      (setf (aref freqArray index) nil)

      (setf newest (list
                    (+ (car first)(car second))
                    nil
                    first
                    second))
      (setf (aref freqArray index) newest))
    (return-from create-huffman-tree (aref freqArray index))))

(defun print-huffman-tree (localRoot codeList file)
  (if (null localRoot)
    (return localRoot))

  (when (not (null (caddr localRoot)))
    (print-huffman-tree (caddr localRoot) (append codeList '(0)) file))

  (when (not(null(cadr localRoot)))
    (format file "~d: ~a ~%" (cadr localRoot) codeList))

  (when (not (null (cadddr localRoot)))
    (print-huffman-tree (cadddr localRoot) (append codeList '(1)) file)))

(defun BFS-huffman-tree(root file)
  (let ((node-stack (list))(currentNode)(currentCode)(code-stack (list)))
    (setf node-stack(append node-stack (list root)))
    (setf code-stack (append code-stack (list '())))
    (loop
      (if (null (car(last node-stack)))(return nil))

      (setf currentNode (car node-stack))
      (setf node-stack (cdr node-stack))

      (setf currentCode (car code-stack))
      (setf code-stack (cdr code-stack))

      (when (not(null(cadr currentNode)))
        (format file "~a: ~a~%" (cadr currentNode) currentCode))
      (when (not(null (caddr currentNode)))
        (setf node-stack(append node-stack (list(caddr currentNode))))
        (setf code-stack (append code-stack(list (append currentCode '(0))))))
      (when (not(null (cadddr currentNode)))
        (setf node-stack(append node-stack (list(cadddr currentNode))))
        (setf code-stack (append code-stack (list (append currentCode '(1)))))))))

(defun calculate-huffman-codes(srcFileName destFileName)
  (let ((freqArray nil)(huffmanTree nil))
    (with-open-file (out destFileName :direction :output :if-exists :supersede)
      (setf freqTable (calculate-frequency srcFileName))
      (setf freqArray (create-arr-from-table freqTable))
      (setf huffmanTree (create-huffman-tree freqArray))
      ;(print-huffman-tree huffmanTree nil out)
      (BFS-huffman-tree huffmanTree out)
      (close out))))


(calculate-huffman-codes *srcFileName* *destFileName*)
