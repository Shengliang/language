(ns first-app.core
  (:gen-class))

;; hello
(defn hello ([] "hello world"))

;; argcount
(defn argcount
  ([] 0)
  ([x] 1)
  ([x y] 2)
  ([x y & more] (+ (argcount x y) (count more))))
(println (argcount 1 2 3 4 5))

;; lazy seq-producing functions
(defn mytake [n coll]
  (lazy-seq
    (when (pos? n)
      (when-let [s (seq coll)]
       (cons (first s) (mytake (dec n) (rest s)))))))
(println (mytake 7 (cycle [1 2 3 4])))

(defn -main
  [& args]
  (println (hello) )
)
