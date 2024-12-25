#include "highlighter.h"

CodeHighlighter::CodeHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    // Tag highlighting
    tagFormat.setForeground(Qt::darkBlue);
    tagFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("</?\\b\\w+\\b[^>]*>");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    // Attribute highlighting
    attributeFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegularExpression("\\b\\w+\\b(?=\\=)");
    rule.format = attributeFormat;
    highlightingRules.append(rule);

    // Value highlighting
    valueFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\"[^\"\\n]*\"");
    rule.format = valueFormat;
    highlightingRules.append(rule);

    // Comment highlighting
    commentFormat.setForeground(Qt::darkGray);
    rule.pattern = QRegularExpression("<!--[^>]*-->");
    rule.format = commentFormat;
    highlightingRules.append(rule);

}

void CodeHighlighter::highlightBlock(const QString& text) {
    for (const HighlightingRule& rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}