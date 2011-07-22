package compbio.stat.servlet.util;

import java.util.Date;
import java.util.Map;

import compbio.stat.collector.StatProcessor;
import compbio.ws.client.Services;

public class Totals {
	int total;
	int incomplete;
	int abandoned;
	int cancelled;
	int failed;

	public int getTotal() {
		return total;
	}

	public int getIncomplete() {
		return incomplete;
	}

	public int getAbandoned() {
		return abandoned;
	}

	public int getCancelled() {
		return cancelled;
	}

	public int getFailed() {
		return failed;
	}

	public static Totals sumOfTotals(Map<Date, Totals> stat) {
		Totals total = new Totals();
		for (Map.Entry<Date, Totals> entry : stat.entrySet()) {
			Totals mtotal = entry.getValue();
			total.total += mtotal.getTotal();
			total.incomplete += mtotal.getIncomplete();
			total.abandoned += mtotal.getAbandoned();
			total.cancelled += mtotal.getCancelled();
			total.failed += mtotal.getFailed();
		}
		return total;
	}

	public static Totals sumStats(Map<Services, StatProcessor> stat) {
		Totals total = new Totals();
		for (Map.Entry<Services, StatProcessor> serv : stat.entrySet()) {
			total.total += serv.getValue().getJobNumber();
			total.incomplete += serv.getValue().getIncompleteJobs().size();
			total.abandoned += serv.getValue().getAbandonedJobs().size();
			total.cancelled += serv.getValue().getCancelledJobs().size();
			total.failed += serv.getValue().getFailedJobs().size();
		}
		return total;
	}
}