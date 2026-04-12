#include "SettingsDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSettings>
#include "structs.h"

extern SettingsStruct settings;

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Application Settings");
    setMinimumWidth(300);

    
    renderLitFlat = new QCheckBox("RenderLitFlat", this);
    renderUnlit = new QCheckBox("renderUnlit", this);
    renderLitBump = new QCheckBox("renderLitBump", this);
    renderUnlitTS = new QCheckBox("renderUnlitTS", this);

    renderLitFlat->setChecked(settings.renderLitFlat);
    renderUnlit->setChecked(settings.renderUnlit);
    renderLitBump->setChecked(settings.renderLitBump);
    renderUnlitTS->setChecked(settings.renderUnlitTS);

    auto* formLayout = new QFormLayout();
    formLayout->addRow(renderLitFlat);
    formLayout->addRow(renderUnlit);
    formLayout->addRow(renderLitBump);
    formLayout->addRow(renderUnlitTS);

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_buttonBox);
}