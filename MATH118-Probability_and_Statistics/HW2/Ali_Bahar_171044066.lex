\documentclass[a4 paper]{article}
\usepackage[inner=2.0cm,outer=2.0cm,top=2.5cm,bottom=2.5cm]{geometry}
\usepackage{setspace}
\usepackage[ruled]{algorithm2e}
\usepackage[rgb]{xcolor}
\usepackage{verbatim}
\usepackage{subcaption}
\usepackage{amsgen,amsmath,amstext,amsbsy,amsopn,tikz,amssymb}
\usepackage{fancyhdr}
\usepackage[colorlinks=true, urlcolor=blue,  linkcolor=blue, citecolor=blue]{hyperref}
\usepackage[colorinlistoftodos]{todonotes}
\usepackage{rotating}
\usepackage{booktabs}
\newcommand{\ra}[1]{\renewcommand{\arraystretch}{#1}}

\usepackage{listings}
\usepackage{xcolor}

\definecolor{codegreen}{rgb}{0,0.6,0}
\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\definecolor{codepurple}{rgb}{0.58,0,0.82}
\definecolor{backcolour}{rgb}{0.95,0.95,0.92}

\lstset{frame=tb,
  backgroundcolor=\color{backcolour},   
    commentstyle=\color{codegreen},
    keywordstyle=\color{magenta},
    numberstyle=\tiny\color{codegray},
    stringstyle=\color{codepurple},
    basicstyle=\ttfamily\footnotesize,
    breakatwhitespace=false,         
    breaklines=true,                 
    captionpos=b,                    
    keepspaces=true,                 
    numbers=left,                    
    numbersep=5pt,                  
    showspaces=false,                
    showstringspaces=false,
    showtabs=false,                  
    tabsize=2
}


\newtheorem{thm}{Theorem}[section]
\newtheorem{prop}[thm]{Proposition}
\newtheorem{lem}[thm]{Lemma}
\newtheorem{cor}[thm]{Corollary}
\newtheorem{defn}[thm]{Definition}
\newtheorem{rem}[thm]{Remark}
\numberwithin{equation}{section}

\newcommand{\homework}[6]{
	\pagestyle{myheadings}
	\thispagestyle{plain}
	\newpage
	\setcounter{page}{1}
	\noindent
	\begin{center}
		\framebox{
			\vbox{\vspace{2mm}
				\hbox to 6.28in { {\bf MATH 118:~Statistics and Probability \hfill {\small (#2)}} }
				\vspace{6mm}
				\hbox to 6.28in { {\Large \hfill #1  \hfill} }
				\vspace{6mm}
				\hbox to 6.28in { {\it Instructor: {\rm #3} \hfill Name: {\rm #5} \hfill Student Id: {\rm #6}} \hfill}
				\hbox to 6.28in { {\it Assistant: #4  \hfill #6}}
				\vspace{2mm}}
		}
	\end{center}
	\markboth{#5 -- #1}{#5 -- #1}
	\vspace*{4mm}
}

\newcommand{\problem}[2]{~\\\fbox{\textbf{Problem #1}}\hfill (#2 points)\newline\newline}
\newcommand{\subproblem}[1]{~\newline\textbf{(#1)}}
\newcommand{\D}{\mathcal{D}}
\newcommand{\Hy}{\mathcal{H}}
\newcommand{\VS}{\textrm{VS}}
\newcommand{\solution}{~\newline\textbf{\textit{(Solution)}} }

\newcommand{\bbF}{\mathbb{F}}
\newcommand{\bbX}{\mathbb{X}}
\newcommand{\bI}{\mathbf{I}}
\newcommand{\bX}{\mathbf{X}}
\newcommand{\bY}{\mathbf{Y}}
\newcommand{\bepsilon}{\boldsymbol{\epsilon}}
\newcommand{\balpha}{\boldsymbol{\alpha}}
\newcommand{\bbeta}{\boldsymbol{\beta}}
\newcommand{\0}{\mathbf{0}}


\begin{document}
	\homework{Homework \#2}{Due: 07/06/21}{Dr. Zafeirakis Zafeirakopoulos}{Gizem S\"ung\"u}{Ali Bahar}{171044066}
	\textbf{Course Policy}: Read all the instructions below carefully before you start working on the assignment, and before you make a submission.
	\begin{itemize}
		\item It is not a group homework. Do not share your answers to anyone in any circumstance. Any cheating means at least -100 for both sides. 
		\item Do not take any information from Internet.
		\item No late homework will be accepted. 
		\item For any questions about the homework, send an email to gizemsungu@gtu.edu.tr.
		\item Submit your homework (both your latex and pdf files in a zip file) into the course page of Moodle.
		\item Save your latex, pdf and zip files as "Name\_Surname\_StudentId".\{tex, pdf, zip\}.
		\item The answer which has only calculations without any formula and any explanation will get zero. 
		\item The deadline of the homework is 07/06/20 23:55.
		\item I strongly suggest you to write your homework on \LaTeX. However, hand-written paper is still accepted \textbf{IFF} your hand writing is \textbf{clear and understandable to read}, and the paper is well-organized. Otherwise, I cannot grade your homework.
		\item You do not need to write your Student Id on the page above. I am checking your ID from the file name.
	\end{itemize}
	
	\problem{1:}{10+10+10+10+10+10+40 = 100}
	\textbf{WARNING:} Please show your OWN work. Any cheating can be easily detected and will not be graded.
	\newline
	\newline
	For the question, please follow the file called manufacturing\_defects.txt while reading the text below.\\
	\newline
	In each year from 2000 to 2019, the number of manufacturing defects in auto manufacturers were counted. The data was collected from 14 different auto manufactory companies. The numbers of defects for the companies are indicated in 14 columns following the year column. Assume that the number of manufacturing defects per auto company per year is a random variable having a Poisson($\lambda$) and that the number of defects in different companies or in different years are independent.\\
	(Note: You should implement a code for your calculations for each following subproblem. You are free to use any programming languages (Python, R, C, C++, Java) and their related library.)
	
	\subproblem{a} Give a table how many cases occur for all companies between 2000 and 2019 for each number of defects (\# of Defects).\\
	Hint: When you check the file you will see: \# of Defects = \{0, 1, 2, 3, 4\}.\\
	\begin{table}[htb!]
		\centering
		\begin{tabular}{c|c}
			\begin{tabular}[c]{@{}c@{}}\textbackslash{}\# of\\Defects\end{tabular} & \begin{tabular}[c]{@{}c@{}}\textbackslash{}\# of cases\\in all company \\between the years\end{tabular}  \\ 
			\hline
			0                                                                      & 144                                                                                                         \\
			1                                                                      & 91                                                                                                         \\
			2                                                                      & 32                                                                                                         \\
			3                                                          & 11
			\\
			4                                                                      & 2                                                                                                       
		\end{tabular}
		
		\caption{Actual cases}
		\label{tab1}
	\end{table}
	
	\subproblem{b} Estimate $\lambda$ from the given data. \\
    $\lambda$ = total number of event / total number of cases \\
    $\lambda$ = total number of defects / total number of cases \\
	total number of defects = (0 * 144) + (1 * 91) + (2 * 32) + (3 * 11) + (4 * 2) = 196 \\
	total number of cases = 144 + 91 + 32 + 11 + 2 = 280 \\
	$\lambda$ = 196 / 280 = 0.7
	
	
	\subproblem{c} Update Table \ref{tab1} in Table \ref{tab2} with Poisson predicted cases with the estimated $\lambda$.\\
	\begin{table}[htb!]
		\centering
		\begin{tabular}{c|c|c}
			\begin{tabular}[c]{@{}c@{}}\textbackslash{}\# of\\Defects\end{tabular} & \begin{tabular}[c]{@{}c@{}}\textbackslash{}\# of cases\\in all companies\\between the years\end{tabular} & \begin{tabular}[c]{@{}c@{}}Predicted \textbackslash{}\# of cases\\in all companies\\between the years\end{tabular}  \\ 
			\hline
			0                                                                      & 144                                                                                                         & 139.04                                                                                                                    \\
			1                                                                      & 91                                                                                                         & 97.33                                                                                                                     \\
			2                                                                      & 32                                                                                                         & 34.06                                                                                                                     \\
			3                                                                      & 11                                                                                                         & 7.94    
			\\
			4                                                                      & 2                                                                                                         & 1.39                                                                                                                 
		\end{tabular}
		\caption{Actual vs. Predicted Cases}
		\label{tab2}
	\end{table}
	\subproblem{d} Draw a barplot for the actual cases (Table \ref{tab2} in column 2) and the predicted cases (Table \ref{tab2} column 3) with respect to \# of defecrs. You should put the figure.\\
	\includegraphics[width=\textwidth,height=\textheight,keepaspectratio]{barplot.png}
	
	\subproblem{e} According to the barplot in (c), does the poisson distribution fit the data well? Compare the values of the actual cases and the values of the poisson predicted cases, and write your opinions about performance of the distribution.\\ \\
	differences are:
	\begin{itemize}
	    \item {144 - 139.04 = 4.96}
	    \item {91- 97.33 = -6.33}
	    \item {32 - 34.06 = -2.6}
	    \item {11 - 7.94 = 3.06}
	    \item {2- 1.39 = 0.61}
	\end{itemize}
	I can say that distribution fit the data well.
	
	\subproblem{f} According to your estimations above, write your opinions considering your barplot and Table \ref{tab2}. Which company do you prefer to buy a car? Why?\\
	\subproblem{f Updated} According to your estimations above, write your opinions considering your barplot and Table 2. Do you
think that road transportation is dangerous for us? Whether yes or no, explain your reason. \\
    We do not know that what kind of defects the vehicles have, so i assume that this defect might cause to fatal accident.\\
    We do not know how many vehicle is produced at total.\\
    If these defects could be detected in company, then there is no problem.\\
    If these defects could not be detected in company, we should know how many vehicle is produced at total to be able to say whether it is dangerous or not.\\

	\subproblem{g} Paste your code that you implemented for the subproblems above. Do not forget to write comments on your code.\\
	Example:\\
	\begin{itemize}
		\item {The common code block for all subproblems\\
		Paste here. Your code should read the file and compute other things which the following subproblems need.
		\begin{lstlisting}[language=Python]
import math
import matplotlib . pyplot as plt
import numpy as np

filep = open("manufacturing_defects.txt", "r")

file_txt = filep.read()

filep.close()

file_lines = file_txt.split('\n')
		\end{lstlisting}
		}
		\item {The code block for (a)\\
		Paste here. Your code should compute the values in Table \ref{tab1} column 2.
		\begin{lstlisting}[language=Python]
cases = {}
for curr_line in file_lines:
    line_items = curr_line.split('\t')

    for element in line_items[2:]:
        x = int(element)

        if x in cases:
            cases[x] += 1
        else:
            cases[x] = 1

print("\# of Defects\t|\# of cases in all company between the years")
print(64 * "-")
for case in cases:
    print(case, end='')
    print("\t\t|", end='')
    print(cases[case])
		\end{lstlisting}
		}
		\item {The code block for (b)\\
		Paste here. Your code should compute $\lambda$.
		\begin{lstlisting}[language=Python]
total_number_of_defects = 0
total_number_of_cases = 0
for case in cases:
    total_number_of_defects += case * cases[case]
    total_number_of_cases += cases[case]

the_lambda = total_number_of_defects / total_number_of_cases

print(f"Total number of defects is {total_number_of_defects}")
print(f"Total number of cases {total_number_of_cases}")
print(f"Lambda is {the_lambda}")
		\end{lstlisting}
		}
		\item {The code block for (c)\\
		Paste here. Your code should compute the values in Table \ref{tab2} column 3. 
		\begin{lstlisting}[language=Python]
predicted_cases = {}
for case in cases:
    predicted_cases[case] = (((math.e ** (-1 * the_lambda)) * (the_lambda ** case)) / math.factorial(case)) * total_number_of_cases

print("\# of Defects\t|\# of cases in all company between the years\t|Predicted \# of cases in all companies between the years")
print(122 * "-")
for case in cases:
    print(case, end='')
    print("\t\t|", end='')
    print(cases[case], end='')
    print("\t\t\t\t\t\t|", end='')
    print(predicted_cases[case])
		\end{lstlisting}
		}
		\item {The code block for (d)\\
		Paste here. Your code should draw the barplot.
		\begin{lstlisting}[language=Python]
a_range = np.arange(len(cases))

actual_plt = plt.bar(a_range - 0.1, list(cases.values()), 0.2, label='actual', color = '#000000')
predicted_plt = plt.bar(a_range + 0.1, list(predicted_cases.values()), 0.2, label='predicted', color = '#808080')

plt.xlabel("Number of defects")
plt.ylabel("Number of cases")
plt.title("Actual cases and The predicted cases")
plt.xticks(a_range)
plt.legend()
plt.tight_layout()
plt.show()
		\end{lstlisting}
		}
	\end{itemize}

\end{document} 
