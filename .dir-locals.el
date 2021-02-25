;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ((nil . ((eval . (setq                                                                                                    ;;
;;                   projectile-project-test-cmd #'counsel-test-ctest                                                        ;;
;;                   projectile-project-compilation-cmd #'counsel-compile                                                    ;;
;;                   projectile-project-compilation-dir "build"                                                              ;;
;;                   helm-make-build-dir (projectile-compilation-dir)                                                        ;;
;;                   helm-ctest-dir (projectile-compilation-dir)                                                             ;;
;;                   ))                                                                                                      ;;
;;          (projectile-project-name . "omega")                                                                              ;;
;;          (projectile-project-run-cmd . "make && cd test && ./omega_test")                                                 ;;
;;          (projectile-project-configure-cmd . "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B") ;;
;;          (counsel-compile-make-args . "-j7"))))                                                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

((nil . ((eval . (setq
                  projectile-project-test-cmd #'helm-ctest
                  projectile-project-compilation-cmd #'helm-make-projectile
                  projectile-project-compilation-dir "build"
                  helm-make-build-dir (projectile-compilation-dir)
                  helm-ctest-dir (projectile-compilation-dir)
                  ))
         (cmake-ide-project-dir . "~/Projects/omega")
         (cmake-ide-build-dir . "~/Projects/omega/build")
         (cmake-ide-cmake-opts . "-DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON")
         (ccls-initialization-options . (:compilationDatabaseDirectory "build"
                                                                       :cache (:directory "build/.ccls-cache")))
         (projectile-project-name . "omega")
         (projectile-project-run-cmd . "make && cd test && ./omega_test")
         (projectile-project-configure-cmd . "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .")
         (helm-make-args . "-j7"))))
