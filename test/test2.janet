(use ../build/freja-jaylib)

(set-trace-log-callback nil)

(init-window 800 600 "Test Game")
(set-target-fps 60)

(def lenna (load-image-1 "test/lenna.png"))
(image-dither lenna 4 4 4 4)
(def lenna-t (load-texture-from-image lenna))

(def t2 (load-render-texture 200 200))
(begin-texture-mode t2)
(clear-background :white)
(end-texture-mode)

(def buf (array/new (* 100 100)))

(loop [y :range [0 100]
       x :range [0 100]]
  (put buf (+ (* y 100) x) 0xffff00ff))

(update-texture-rec
  (get-render-texture t2)
  [0 0 100 100]
  buf)

(pp (get-image-data (get-texture-data (get-render-texture t2))))

(def cells (gen-image-cellular 100 100 10))
(def cells-t (load-texture-from-image cells))

(while (not (window-should-close))
  (begin-drawing)
  (clear-background :green)

  (draw-texture lenna-t 100 100 :white)
  (draw-texture cells-t 600 0 :white)

  (draw-texture (get-render-texture t2) 300 300 :white)

  (end-drawing))

(close-window)
