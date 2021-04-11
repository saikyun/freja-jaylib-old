(use ../build/jaylib)

(set-config-flags
  :msaa-4x-hint)

(init-window 800 600 "Chart")
(init-audio-device)
(set-target-fps 60)

(while (not (window-should-close))
  (begin-drawing)
  
  (clear-background [0 0 0])
  
  (def [mx my] (get-mouse-position))  
  (def mr [(- mx 15) (- my 15) 30 30])
  (draw-rectangle-rec mr :blue)  
  
  (loop [x :range [20 (+ 40 (get-screen-width)) 40]
         y :range [20 (+ 40 (get-screen-height)) 40]
         :let [r [x y 30 30]]]
    (draw-rectangle-rec r
                        (if (check-collision-recs
                              r
                              mr)
                          :yellow
                          :green)))
  
  (end-drawing))

(close-window)
