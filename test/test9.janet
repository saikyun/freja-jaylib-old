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

(while (not (window-should-close))
  (update-camera c)
  (begin-drawing)
  (clear-background :black)

  (begin-mode-3d c)

  (draw-model model map-pos 1 :white)

  (end-mode-3d)

  (end-drawing))

(close-window)
