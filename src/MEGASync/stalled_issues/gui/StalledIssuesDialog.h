#ifndef STALLEDISSUESDIALOG_H
#define STALLEDISSUESDIALOG_H

#include "MegaDelegateHoverManager.h"
#include "StalledIssue.h"

#include <QDialog>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class StalledIssuesDialog;
}

class StalledIssueTab;

class StalledIssuesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StalledIssuesDialog(QWidget *parent = nullptr);
    ~StalledIssuesDialog();

protected:
    bool eventFilter(QObject *, QEvent *) override;

private slots:
    void on_doneButton_clicked();
    void on_updateButton_clicked();
    void onStalledIssuesModelCountChanged();

    void toggleTab(StalledIssueFilterCriterion filterCriterion);

private:
    Ui::StalledIssuesDialog *ui;
    MegaDelegateHoverManager mViewHoverManager;
    StalledIssueFilterCriterion mCurrentTab;

};

#endif // STALLEDISSUESDIALOG_H
