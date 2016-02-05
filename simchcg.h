#ifndef CARTWRIGHT_SIMCHCG_H
#define CARTWRIGHT_SIMCHCG_H

#include <gtkmm/drawingarea.h>

#include "worker.h"
#include <boost/timer/timer.hpp>

#include <tuple>

class SimCHCG : public Gtk::DrawingArea
{
public:
    SimCHCG(int width, int height, double mu, int delay, bool fullscreen);
    virtual ~SimCHCG();

    void name(const char* n) {
        name_ = n;
    }
    void name_scale(double n) {
        font_name_.set_size(n*48*PANGO_SCALE);
    }

    typedef sigc::signal<void> signal_queue_draw_t;
    signal_queue_draw_t signal_queue_draw() {
        return signal_queue_draw_;
    }

protected:
    bool device_to_cell(int *x, int *y);
    void create_our_pango_layouts();
    void create_icon_box();

    //Override default signal handler:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    virtual void on_realize() override;
    virtual void on_unrealize() override;
    virtual void on_size_allocate(Gtk::Allocation& allocation) override;
    virtual void on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen) override;

    virtual bool on_button_press_event(GdkEventButton* button_event) override;
    virtual bool on_motion_notify_event(GdkEventMotion* motion_event) override;
    virtual bool on_key_press_event(GdkEventKey* key_event) override;

    int device_width_, device_height_;
    int grid_width_, grid_height_;
    double mu_;
    bool fullscreen_;

    std::string name_{"Human and Comparative Genomics Laboratory"};

    double cairo_scale_;

    double width_, height_;
    double east_, north_, west_, south_;

    int lastx_{-1}, lasty_{-1};

    Glib::RefPtr<Gdk::Pixbuf> logo_;
    Glib::RefPtr<Gdk::Cursor> none_cursor_, cell_cursor_;
    sigc::connection cursor_timeout_;

	Pango::FontDescription font_name_, font_note_, font_icon_;
    std::pair<double,double> pos_name_, pos_note_, pos_icon_, pos_logo_;

    Glib::RefPtr<Pango::Layout> layout_name_, layout_note_, layout_icon_;

    Cairo::RefPtr<Cairo::Region> box_icon_;

    Worker worker_;
    Glib::Threads::Thread* worker_thread_{nullptr};


    signal_queue_draw_t signal_queue_draw_;
};

#endif
