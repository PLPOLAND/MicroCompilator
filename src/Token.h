#ifndef TOKEN_H
#define TOKEN_H
/**
*@brief Tokeny
*
 */
enum Token
{
    ///epsilon
    Null,
    ///"PROGRAM"
    ProgramSym,
    ///"BEGIN"
    BeginSym,
    ///"END."
    EndProgramSym,
    ///"END"
    EndSym,
    ///"READ"
    ReadSym,
    ///"WRITE"
    WriteSym,
    ///"VAR"
    VarSym,
    ///"IF"
    IfSym,
    ///"THEN"
    ThenSym,
    ///"WHILE"
    WhileSym,
    ///"DO"
    DoSym,
    Id,
    ///"INTEGER"
    IntSym,
    IntLiteral,
    ///"REAL"
    RealSym,
    RealLiteral,
    ///"+"
    Plus,
    ///"-"
    Minus,
    ///"*"
    Multiply,
    ///"/"
    Devide,
    ///"<"
    Less,
    ///"<="
    LessEq,
    ///">"
    Greater,
    ///">="
    GreaterEq,
    /// "="
    Equal,
    ///"<>"
    Diffrent,
    ///"("
    LParen,
    ///")"
    RParen,
    ///":="
    Assign,
    ///":"
    Colon,
    ///";"
    SemiColon,
    ///","
    Comma,
    EofSym,
    ErrorSym
};

#endif // !TOKEN_H