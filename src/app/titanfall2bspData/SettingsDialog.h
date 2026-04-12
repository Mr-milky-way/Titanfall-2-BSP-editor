#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QSettings>

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget* parent = nullptr);

    bool RenderLitFlat() const { return renderLitFlat->isChecked(); }
    bool RenderUnlit() const { return renderUnlit->isChecked(); }
    bool RenderLitBump() const { return renderLitBump->isChecked(); }
    bool RenderUnlitTS() const { return renderUnlitTS->isChecked(); }

private:
    QCheckBox* renderLitFlat;
    QCheckBox* renderUnlit;
    QCheckBox* renderLitBump;
    QCheckBox* renderUnlitTS;
    QDialogButtonBox* m_buttonBox;
};

#endif