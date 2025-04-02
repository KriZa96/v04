#include "nwpwin.h"

class ship : public vsite::nwp::window {
public:
	ship(uint8_t size_x, uint8_t size_y):
		moving_speed_(0), 
		size_x_(size_x), 
		size_y_(size_y) {}

	std::string class_name() override {
		return "STATIC";
	}

	void create_ship(vsite::nwp::window window_) {
		if (!*this) {
			create(window_, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, "X", 0, current_position_.x, current_position_.y, size_x_, size_y_);
		}
		reset_position();
	}

	void set_current_position(const POINT& position) {
		current_position_ = position;
	}

	void stop_moving() {
		moving_speed_ = 0;
		reset_style();
	}

	void set_moving_speed(const int moving_speed) {
		moving_speed_ = moving_speed;
		reset_style();
	}

	void move(const RECT& window_size, const int key_press) {
		switch (key_press) {
		case VK_UP:
			move_up(window_size);
			break;
		case VK_DOWN:
			move_down(window_size);
			break;
		case VK_LEFT:
			move_left(window_size);
			break;
		case VK_RIGHT:
			move_right(window_size);
			break;
		}
	}
private:
	int moving_speed_;
	POINT current_position_;
	uint8_t size_x_;
	uint8_t size_y_;

	void reset_style() {
		auto style = GetWindowLong(*this, GWL_STYLE);
		if (moving_speed_ > 0) {
			style |= WS_BORDER;
		}
		else if (style & WS_BORDER) {
			style &= ~WS_BORDER;
		}
		SetWindowLong(*this, GWL_STYLE, style);
		reset_position();
	}

	void reset_position() {
		SetWindowPos(*this, 0, current_position_.x, current_position_.y, 0, 0,  SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}

	void move_up(const RECT& window_size) {
		current_position_.y = (
			current_position_.y - moving_speed_ >= window_size.top ?
			current_position_.y - moving_speed_ :
			window_size.bottom
			);
		reset_position();
	}

	void move_down(const RECT& window_size) {
		current_position_.y = (
			current_position_.y + moving_speed_ <= window_size.bottom ?
			current_position_.y + moving_speed_ :
			window_size.top
			);
		reset_position();
	}

	void move_left(const RECT& window_size) {
		current_position_.x = (
			current_position_.x - moving_speed_ >= window_size.left ?
			current_position_.x - moving_speed_ :
			window_size.right
			);
		reset_position();
	}

	void move_right(const RECT& window_size) {
		current_position_.x = (
			current_position_.x + moving_speed_ <= window_size.right ?
			current_position_.x + moving_speed_ :
			window_size.left
			);
		reset_position();
	}
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		ship_.set_current_position(p);
		ship_.create_ship(*this);
	}
	void on_key_up(int vk) override {
		if (ship_) ship_.stop_moving(); 
	}
	void on_key_down(int vk) override {
		if (!ship_) return;

		RECT window_size;
		bool is_window_present = GetClientRect(*this, &window_size);

		ship_.set_moving_speed(GetKeyState(VK_CONTROL) < 0 ? 10 : 5);
		ship_.move(window_size, vk);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	ship ship_{10, 20};
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
