((nil . ((eval . (setq
                  projectile-project-test-cmd #'counsel-test-ctest
                  projectile-project-compilation-cmd #'counsel-compile
                  projectile-project-compilation-dir "build"
                  ;;helm-make-build-dir (projectile-compilation-dir)
                  ;;helm-ctest-dir (projectile-compilation-dir)
                  ))
         (projectile-project-name . "omega")
         (projectile-project-run-cmd . "make && cd test && ./omega_test")
         (projectile-project-configure-cmd . "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B")
         (counsel-compile-make-args . "-j7"))))
