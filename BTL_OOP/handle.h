#ifndef HANDLE_H
#define HANDLE_H


class handle {
public:
    static void handle_view_login();
    static void handle_view_admin_menu();

    static void handle_view_enter_username();

    static void handle_view_enter_password();

    static void handle_view_alert_login_success();

    static void handle_view_alert_login_unsuccessful();

    static void handle_view_alert_choose_invalid();

    static void handle_view_movie_management();

    static void handle_view_ticket_management();

    static void handle_view_customer_management();

    static void handle_view_seat_management();

    static void handle_view_banner_update_customer();


    static void handle_view_banner_list_customer();

    static void handle_view_alert_add_customer_success();

    static void handle_view_banner_add_customer();

    static void handle_view_banner_empty_customer();

    static void handle_view_list_customer();
};


#endif //HANDLE_H
