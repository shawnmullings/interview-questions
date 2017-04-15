using System.Web.Http;
using System.Net.Http.Headers;

namespace kofile_c_charp
{
	public static class WebApiConfig
	{
		public static void Register(HttpConfiguration config)
		{
			// Web API configuration and services
			config.Formatters.JsonFormatter.SupportedMediaTypes.Add(new MediaTypeHeaderValue("application/json"));  
			config.Formatters.Remove(config.Formatters.XmlFormatter);  

			// Web API routes
			config.MapHttpAttributeRoutes();

			config.Routes.MapHttpRoute(
				name: "Api",
				routeTemplate: "api/{controller}"
			);
		}
	}
}
