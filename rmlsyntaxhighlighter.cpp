#include "rmlsyntaxhighlighter.hpp"

CRMLSyntaxHighlighter::CRMLSyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    HighlightingRule Rule;

    mTagFormat.setForeground(Qt::darkRed);
    mTagFormat.setFontWeight(QFont::Bold);

    mAttributeFormat.setForeground(Qt::darkBlue);

    mStringFormat.setForeground(Qt::darkGreen);
    mStringFormat.setFontItalic(true);

    Rule.mPattern = QRegExp("<([A-Z][A-Z0-9]*)\\b");
    Rule.mPattern.setCaseSensitivity(Qt::CaseInsensitive);
    Rule.mFormat = mTagFormat;
    mHighlightingRules.append(Rule);

    Rule.mPattern = QRegExp("</([A-Z][A-Z0-9]*)\\b");
    Rule.mPattern.setCaseSensitivity(Qt::CaseInsensitive);
    Rule.mFormat = mTagFormat;
    mHighlightingRules.append(Rule);

    Rule.mPattern = QRegExp("/*>");
    Rule.mPattern.setCaseSensitivity(Qt::CaseInsensitive);
    Rule.mFormat = mTagFormat;
    mHighlightingRules.append(Rule);

    Rule.mPattern = QRegExp("([A-Z][A-Z0-9]*)\\b=");
    Rule.mPattern.setCaseSensitivity(Qt::CaseInsensitive);
    Rule.mFormat = mAttributeFormat;
    mHighlightingRules.append(Rule);

    Rule.mPattern = QRegExp("\"[^\"\\r\\n]*\"");
    Rule.mPattern.setCaseSensitivity(Qt::CaseInsensitive);
    Rule.mFormat = mStringFormat;
    mHighlightingRules.append(Rule);

    mCommentStartExpression =  QRegExp("<!--");
    mCommentEndExpression = QRegExp("-->");

    mMultiLineCommentFormat.setForeground(Qt::lightGray);
    mMultiLineCommentFormat.setFontItalic(true);
}

void CRMLSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, mHighlightingRules)
    {
        QRegExp expression(rule.mPattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.mFormat);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = mCommentStartExpression.indexIn(text);

    while (startIndex >= 0)
    {
        int endIndex = mCommentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                    + mCommentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, mMultiLineCommentFormat);
        startIndex = mCommentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
