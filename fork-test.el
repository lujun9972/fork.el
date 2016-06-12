(add-to-list 'load-path (file-name-directory buffer-file-name))
(require 'fork-core)
(message "%d" (fork))
