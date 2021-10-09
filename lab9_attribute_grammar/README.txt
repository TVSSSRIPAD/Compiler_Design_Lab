NOTE:

    1) Negative Integers are also supported in the attached implementation
    2) Along with the standard mathematical operations like addition, subtraction, multiplication, division, 
        Mod operation, Power operator, Brackets are also considered in the attached implementation. 
    3) Mod operator is to be written  as : 5 % 2
    4) Power is to be written as :  2**3 (which is 2 raised to power of 3)
    5) lexan.l file has code for lexical analyser
    6) parser.y file has code for parser generator

    The final attribute grammar is:-
    
    E   -> E  ‘+’ T   { E.val = E1.val + T.val }
    | E  ‘-’ T { E.val = E2.val - T.val }
        | T { E.val =  T.val}  

    T   -> T ‘*’ S { T.val = T.val * S.val }
        | T ‘**’ S { T.val = power(T.val , S.val)  }
        | T ‘%’ S { T.val = T.val % S.val  }
        | T ‘/’ S { T.val = T.val / S.val  }
        | S {T.val = S.val } 

    S   -> num { S.val = num }
        | ‘-’ num { S.val = -num }
        | ‘(‘ E ‘)’ { S.val = E.val }

Steps to run:
    Run the run.sh script using the command ./run.sh.
