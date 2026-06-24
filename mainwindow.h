#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include "flight.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {}

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_btnAdminLogin_clicked();
    void on_btnPassengerLogin_clicked();
    void on_adminMenu_AddFlight_clicked();
    void on_adminMenu_ShowFlights_clicked();
    void on_adminMenu_TotalFlights_clicked();
    void on_adminMenu_Confidential_clicked();
    void on_adminMenu_Passengers_clicked();
    void on_adminMenu_Revenue_clicked();
    void on_adminMenu_SeatAlloc_clicked();
    void on_adminMenu_Back_clicked();
    void on_btnAddFlight_clicked();
    void on_btnAddFlight_Back_clicked();
    void on_btnDataView_Back_clicked();
    void on_passMenu_Book_clicked();
    void on_passMenu_View_clicked();
    void on_passMenu_Cancel_clicked();
    void on_passMenu_Back_clicked();
    void on_btnBookTicket_clicked();
    void on_btnBook_Back_clicked();
    void on_btnView_Back_clicked();
    void on_btnCancelTicket_clicked();
    void on_btnCancel_Back_clicked();

private:
    QStackedWidget *stackedWidget;

    enum Pages {
        PAGE_LOGIN        = 0,
        PAGE_ADMIN_MENU   = 1,
        PAGE_ADD_FLIGHT   = 2,
        PAGE_DATA_VIEW    = 3,
        PAGE_PASS_MENU    = 4,
        PAGE_BOOK         = 5,
        PAGE_VIEW_TICKETS = 6,
        PAGE_CANCEL       = 7
    };

    // Login
    QLineEdit *txtUsername, *txtPassword;

    // Add Flight
    QLineEdit *txtFlightNo, *txtAirline, *txtDestination;
    QLineEdit *txtDeparture, *txtArrival, *txtSeats;

    // Data View
    QTextEdit *txtDataOutput;
    QLabel    *lblDataTitle;

    // Passenger - Book
    QLineEdit *txtPassName, *txtPassSeat;
    QComboBox *cmbFlights;       // Flight dropdown
    QComboBox *cmbClass, *cmbPayment;
    QTextEdit *txtBookOutput;

    // Passenger - View
    QTextEdit *txtViewOutput;

    // Passenger - Cancel
    QLineEdit *txtCancelName, *txtCancelFlight, *txtCancelSeat;

    // Background
    QPixmap bgImage;

    // Data
    QVector<Flight> flights;
    double totalRevenue = 0;

    // Helpers
    void applyStyle();
    void showDataPage(const QString &title, const QString &content);
    QWidget* buildLoginPage();
    QWidget* buildAdminMenuPage();
    QWidget* buildAddFlightPage();
    QWidget* buildDataViewPage();
    QWidget* buildPassMenuPage();
    QWidget* buildBookPage();
    QWidget* buildViewPage();
    QWidget* buildCancelPage();
    QPushButton* menuCard(const QString &icon, const QString &title,
                          const QString &desc, const QString &color);
    QLabel* makeLabel(const QString &text);
};

#endif