L'Objectif de Minishell est de reproduire le comportement de Bash :
- gestion de commande simple : ls/cat/grep....
- gestion de bulltins : echo/cd/env/export/unset/exit/pwd.
- gestion de pipe : cat | cat | ls / cat "fichier" | grep a.
- gestion des redirection : cat < "fichier" | grep a > "out".
- gestion du heredoc : cat << eof.

