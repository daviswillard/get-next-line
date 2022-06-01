call plug#begin('~/.vim/plugged')

"	highlight statusline
	Plug 'itchyny/lightline.vim'
" 	multi-cursors
	Plug 'mg979/vim-visual-multi', {'branch': 'master'}
" 	tree
	Plug 'preservim/nerdtree'
" 	editconfig
	Plug 'editorconfig/editorconfig-vim'
" 	заменитель vim-lsp
	Plug 'dense-analysis/ale'
"   цветовая схема vim
    Plug 'flazz/vim-colorschemes'
"   автоматическое проставление скобок
    Plug 'tpope/vim-surround'
    Plug 'jiangmiao/auto-pairs'
"   вставка и копирование в буфер обмена
    Plug 'christoomey/vim-system-copy'
"	CoC+МыС
	Plug 'neoclide/coc.nvim', {'do': { -> coc#util#install()}}
call plug#end()

nnoremap <C-o> :NERDTreeToggle<CR>

let g:ale_fixers = {
\	'*': ['remove_trailing_lines', 'trim_whitespace'],
\	'C': ['clang-format'],
\}

let g:ale_fix_on_save = 1

"   еще немного разных настроек для vim
set nocompatible                " choose no compatibility with legacy vi
syntax enable
set showcmd                     " display incomplete commands
filetype plugin indent on       " load file type plugins + indentation

"" Whitespace
set nowrap                      " don't wrap lines
set backspace=indent,eol,start  " backspace through everything in insert mode

"" Searching
set hlsearch                    " highlight matches
set incsearch                   " incremental searching
set ignorecase                  " searches are case insensitive...
set smartcase                   " ... unless they contain at least one capital letter

"	vimrc файл, скопированный с интернета
" Автоотступ
set tabstop=4
set shiftwidth=4
set smarttab
" set expandtab "Ставим табы пробелами
set softtabstop=4 "4 пробела в табе
set autoindent
" Подсвечиваем все что можно подсвечивать
let python_highlight_all = 1
" Включаем 256 цветов в терминале, мы ведь работаем из иксов?
" Нужно во многих терминалах, например в gnome-terminal
set t_Co=256

set nu "Включаем нумерацию строк
set mousehide "Спрятать курсор мыши когда набираем текст
set mouse=a "Включить поддержку мыши
set termencoding=utf-8 "Кодировка терминала
set novisualbell "Не мигать
set t_vb= "Не пищать! (Опции 'не портить текст', к сожалению, нету)
" Удобное поведение backspace
set backspace=indent,eol,start whichwrap+=<,>,[,]
" Вырубаем черточки на табах
set showtabline=1

" Переносим на другую строчку, разрываем строки
set wrap
set linebreak

" Вырубаем .swp и ~ (резервные) файлы
set nobackup
set noswapfile
set encoding=utf-8 " Кодировка файлов по умолчанию
set fileencodings=utf8,cp1251

set clipboard=unnamed
set ruler

set hidden
nnoremap <C-N> :bnext<CR>
nnoremap <C-P> :bprev<CR>

" Выключаем звук в Vim
set visualbell t_vb=

"Переключение табов по CMD+number для MacVim
if has("gui_macvim")
  " Press Ctrl-Tab to switch between open tabs (like browser tabs) to
  " the right side. Ctrl-Shift-Tab goes the other way.
  noremap <C-Tab> :tabnext<CR>
  noremap <C-S-Tab> :tabprev<CR>

  " Switch to specific tab numbers with Command-number
  noremap <D-1> :tabn 1<CR>
  noremap <D-2> :tabn 2<CR>
  noremap <D-3> :tabn 3<CR>
  noremap <D-4> :tabn 4<CR>
  noremap <D-5> :tabn 5<CR>
  noremap <D-6> :tabn 6<CR>
  noremap <D-7> :tabn 7<CR>
  noremap <D-8> :tabn 8<CR>
  noremap <D-9> :tabn 9<CR>
  " Command-0 goes to the last tab
  noremap <D-0> :tablast<CR>
endif

set guifont=Monaco:h18
colorscheme gruvbox

" if hidden is not set, TextEdit might fail.
set hidden
