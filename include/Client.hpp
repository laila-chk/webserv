/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:22:44 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/12 20:05:16 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HP
#define CLIENT_HP

#include "include.hpp"
#include "Cluster.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "parsing.hpp"

class Response;

class Client {
    private:
        Cluster     *_cluster;
        locations   *_matched;
        SOCK_FD     _socket;
        bool        _done_recv;
        bool        _done_send;
        bool        _done_cgi;
        std::string _recv_buffer;
        std::string _send_buffer;

    public:
        Client(Cluster *cluster);
        ~Client(void);
        SOCK_FD get_connect_fd();
        void    recieve(void);
        void    sending(void);
        bool    done_send(void);
        void    parse_header(void);
        void    recv_body(void);

        bool    done_cgi(void);
        void    set_done_cgi(bool state);
        Cluster get_cluster();
//        Request get_req();
        int     pid;
        int     stats;


        Request     *_req;
        Response    *_res;
};
        void    get_matched_location(void);
        Request *get_req(void);
        locations *get_location(); };

#endif
