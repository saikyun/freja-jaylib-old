(use ../build/freja-jaylib)

(set-config-flags :msaa-4x-hint)

(init-window 800 600 "Test Game")
(set-target-fps 60)

(def c (camera-3d :target [0 3 0]
                  :up [0 1 0]
                  :fovy 60
                  :type :perspective
                  :position [6 3 6]))

(def img (load-image-1 "raylib/examples/models/resources/cubicmap.png"))
(def cubic-map (load-texture-from-image img))
(def mesh (gen-mesh-cubicmap img [1 1 1]))
(def model (load-model-from-mesh mesh))

(def texture (load-texture "raylib/examples/models/resources/cubicmap_atlas.png"))
(def mat (get-model-material model 0))
(set-material-texture mat texture :diffuse)

(def map-pixels (get-image-data img))
(unload-image img)

(def map-pos [-16 0 -8])

(set-camera-mode c :orbital)

(def rt (load-render-texture 300
                             300))

(while (not (window-should-close))
  (update-camera c)

  (begin-drawing)

  (rl-push-matrix)
  (rl-translatef 0 100 0)

  (rl-load-identity)

  (do
    (begin-texture-mode rt)
    (rl-draw-render-batch-active)

    (clear-background :green)

    (rl-draw-render-batch-active)

    (do
      (begin-mode-3d c)
      (rl-draw-render-batch-active)
      (draw-model model map-pos 1 :white)
      (rl-draw-render-batch-active)
      (end-mode-3d))

    (rl-draw-render-batch-active)

    (end-texture-mode))

  (rl-pop-matrix)

  (clear-background :black)

  (draw-rectangle 0 0 100 100 :blue)

  (rl-push-matrix)

  (draw-rectangle 0 0 150 100 :orange)

  (comment
    (rl-push-matrix)

    (rl-load-identity)

    (do
      (begin-mode-3d c)
      (rl-draw-render-batch-active)
      (draw-model model map-pos 1 :white)
      (rl-draw-render-batch-active)
      (end-mode-3d))

    (rl-pop-matrix))

  (rl-translatef 0 100 0)

  #  (rl-draw-render-batch-active)

  (draw-rectangle 0 50 100 100 :red)
  #  (rl-draw-render-batch-active)

  (rl-pop-matrix)

  (do comment
    (draw-texture-pro (get-render-texture rt)
                      [0 0 300 -300]
                      [200 0 300 300]
                      [0 0]
                      0
                      :white))
  (end-drawing))

(close-window)
