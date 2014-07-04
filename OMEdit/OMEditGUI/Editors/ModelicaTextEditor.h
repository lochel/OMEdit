/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2014, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */
/*
 *
 * @author Adeel Asghar <adeel.asghar@liu.se>
 *
 * RCS: $Id$
 *
 */

#ifndef MODELICATEXTWIDGET_H
#define MODELICATEXTWIDGET_H

#include <QToolButton>
#include <QSyntaxHighlighter>
#include <QSettings>

#include "MainWindow.h"
#include "Helper.h"
#include "Utilities.h"
#include "BaseEditor.h"

class ModelWidget;
class LineNumberArea;

class CommentDefinition
{
public:
  CommentDefinition();
  CommentDefinition &setAfterWhiteSpaces(const bool);
  CommentDefinition &setSingleLine(const QString &singleLine);
  CommentDefinition &setMultiLineStart(const QString &multiLineStart);
  CommentDefinition &setMultiLineEnd(const QString &multiLineEnd);
  bool isAfterWhiteSpaces() const;
  const QString &singleLine() const;
  const QString &multiLineStart() const;
  const QString &multiLineEnd() const;
  bool hasSingleLineStyle() const;
  bool hasMultiLineStyle() const;
  void clearCommentStyles();
private:
  bool m_afterWhiteSpaces;
  QString m_singleLine;
  QString m_multiLineStart;
  QString m_multiLineEnd;
};

class ModelicaTextEditor : public BaseEditor
{
  Q_OBJECT
public:
  ModelicaTextEditor(ModelWidget *pParent);
  void createActions();
  void setLastValidText(QString validText);
  QStringList getClassNames(QString *errorString);
  bool validateModelicaText();
private:
  ModelWidget *mpModelWidget;
  QString mLastValidText;
  bool mTextChanged;
  QAction *mpToggleCommentSelectionAction;
protected:
  virtual void keyPressEvent(QKeyEvent *pEvent);
signals:
  bool focusOut();
private slots:
  void updateCursorPosition();
  void showContextMenu(QPoint point);
public slots:
  void setPlainText(const QString &text);
  void contentsHasChanged(int position, int charsRemoved, int charsAdded);
  void setLineWrapping();
  void toggleCommentSelection();
};

class ModelicaTextSettings;
class ModelicaTextHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
  ModelicaTextHighlighter(ModelicaTextSettings *pSettings, MainWindow *pMainWindow, QTextDocument *pParent = 0);
  void initializeSettings();
  void highlightMultiLine(const QString &text);
protected:
  virtual void highlightBlock(const QString &text);
private:
  ModelicaTextSettings *mpModelicaTextSettings;
  MainWindow *mpMainWindow;
  struct HighlightingRule
  {
    QRegExp mPattern;
    QTextCharFormat mFormat;
  };
  QVector<HighlightingRule> mHighlightingRules;
  QRegExp mCommentStartExpression;
  QRegExp mCommentEndExpression;
  QRegExp mStringStartExpression;
  QRegExp mStringEndExpression;
  QTextCharFormat mTextFormat;
  QTextCharFormat mKeywordFormat;
  QTextCharFormat mTypeFormat;
  QTextCharFormat mFunctionFormat;
  QTextCharFormat mQuotationFormat;
  QTextCharFormat mSingleLineCommentFormat;
  QTextCharFormat mMultiLineCommentFormat;
  QTextCharFormat mNumberFormat;
public slots:
  void settingsChanged();
};

#endif // MODELICATEXTWIDGET_H