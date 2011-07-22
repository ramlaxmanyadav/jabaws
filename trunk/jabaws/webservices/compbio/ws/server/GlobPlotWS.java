package compbio.ws.server;

import java.util.List;

import javax.jws.WebService;

import org.apache.log4j.Logger;

import compbio.data.msa.JABAService;
import compbio.data.msa.SequenceAnnotation;
import compbio.data.sequence.FastaSequence;
import compbio.metadata.JobSubmissionException;
import compbio.metadata.LimitExceededException;
import compbio.metadata.Option;
import compbio.metadata.Preset;
import compbio.metadata.UnsupportedRuntimeException;
import compbio.metadata.WrongParameterException;
import compbio.runner.disorder.GlobPlot;

@WebService(endpointInterface = "compbio.data.msa.SequenceAnnotation", targetNamespace = JABAService.V2_SERVICE_NAMESPACE, serviceName = "GlobPlotWS")
public class GlobPlotWS extends SequenceAnnotationService<GlobPlot>
		implements
			SequenceAnnotation<GlobPlot> {

	private static Logger log = Logger.getLogger(GlobPlotWS.class);

	public GlobPlotWS() {
		super(new GlobPlot(), log);
	}

	/*
	 * No options are supported, thus the result of this call will be as simple
	 * call to analize without parameters
	 */
	@Override
	public String customAnalize(List<FastaSequence> sequences,
			List<Option<GlobPlot>> options) throws UnsupportedRuntimeException,
			LimitExceededException, JobSubmissionException,
			WrongParameterException {
		return analize(sequences);
	}

	/*
	 * No presets are supported, thus the result of this call will be as simple
	 * call to analize without parameters
	 */
	@Override
	public String presetAnalize(List<FastaSequence> sequences,
			Preset<GlobPlot> preset) throws UnsupportedRuntimeException,
			LimitExceededException, JobSubmissionException,
			WrongParameterException {

		return analize(sequences);
	}

}
