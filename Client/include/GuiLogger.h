#ifndef GUI_LOGGER_H
#define GUI_LOGGER_H
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>


namespace engine
{
	class GuiLogger
	{
	public:
		GuiLogger(GuiLogger const&) = delete;
		void operator=(GuiLogger const&) = delete;
		static GuiLogger& getInstance(void);
		const std::string getCurrentMessage(void);
		void setMessage(const std::string message, bool messageType);
		void updatePosition(const sf::Vector2f position);
		const bool getShowBoolean(void);
		const sf::Text* getText(void) const;

	private:
		GuiLogger();

		sf::Font m_font;
		sf::Text m_text;
		sf::Clock m_clock;
		bool m_show;
	};
}
#endif