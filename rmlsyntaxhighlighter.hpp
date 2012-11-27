#ifndef RMLSYNTAXHIGHLIGHTER_HPP
#define RMLSYNTAXHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QTextDocument>

class CRMLSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit CRMLSyntaxHighlighter(QTextDocument* parent = 0);
    
protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp mPattern;
        QTextCharFormat mFormat;
    };
    QVector<HighlightingRule> mHighlightingRules;

    QTextCharFormat mTagFormat;
    QTextCharFormat mAttributeFormat;
    QTextCharFormat mStringFormat;
    QTextCharFormat mMultiLineCommentFormat;

    QRegExp mCommentStartExpression;
    QRegExp mCommentEndExpression;
};

#endif // RMLSYNTAXHIGHLIGHTER_HPP
