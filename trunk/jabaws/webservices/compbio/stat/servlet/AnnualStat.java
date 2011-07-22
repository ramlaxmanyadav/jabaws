package compbio.stat.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.Date;
import java.util.Map;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import compbio.stat.collector.StatDB;
import compbio.stat.servlet.util.StatCollection;
import compbio.stat.servlet.util.Totals;

public class AnnualStat extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {

		try {
			StatDB db = new StatDB();
			Date earliestRec = db.getEarliestRecord();
			if (earliestRec == null) {
				PrintWriter writer = resp.getWriter();
				writer.println("No statistics found in the database. Please allow "
						+ "at least one hour after a server start for the statistics "
						+ "collector to collect the data. ");
				writer.close();
				return;
			}
			Map<Date, Totals> monthlyTotals = StatCollection
					.getStats(earliestRec);
			req.setAttribute("stat", monthlyTotals);
			req.setAttribute("total", Totals.sumOfTotals(monthlyTotals));

			RequestDispatcher dispatcher = req
					.getRequestDispatcher("statpages/MonthlySummary.jsp");

			req.setAttribute("isAdmin", isAdmin(req));
			dispatcher.forward(req, resp);

		} catch (SQLException e) {
			e.printStackTrace();
			throw new ServletException(e);
		}
	}

	static boolean isAdmin(final HttpServletRequest request) {
		return request.isUserInRole("admin");
	}

}
