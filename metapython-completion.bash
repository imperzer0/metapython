__metapython_completion() {
	local cur prev OPTS
	COMPREPLY=()
	cur="${COMP_WORDS[COMP_CWORD]}"
	prev="${COMP_WORDS[COMP_CWORD - 1]}"
	case $prev in
		'-i' | '--input')
			COMPREPLY=($(compgen -W "$(ls -ap | sed 's/\t/ /')" -- "$cur"))
			return 0
			;;
		'-o' | '--output')
			COMPREPLY=($(compgen -W "$(ls -ap | sed 's/\t/ /')" -- "$cur"))
			return 0
			;;
		'-h' | '--help' | '-V' | '--version' | '-v' | '--verbose')
			return 0
			;;
	esac
	OPTS="
			--input
			--output
			--verbose
			--version
			--help
    	"
	COMPREPLY=($(compgen -W "${OPTS[*]}" -- $cur))
	return 0
}

complete -F __metapython_completion metapython